# include "vm.h"

void	live(t_carry *cr)
{
	unsigned int	dir;
	int				*champ_nbr;

	cr->last_live = 0;
	cr->vm->live_counter++;
	dir = get_param(cr, 0);
	champ_nbr = (int*)&dir;
	if ((champ_nbr[0] * -1) > 0 \
		&& (champ_nbr[0] * -1) <= (int)cr->vm->champs_count)
		cr->vm->last_alive = dir;
	if (cr->vm->v)
		cr->vm->back[cr->position] |= 200;
	if (cr->vm->debug)
	{
		ft_printf("%d ", champ_nbr[0]);
		ft_printf("alive %d! ", cr->vm->last_alive);
	}
}

void	ld(t_carry *cr)
{
	short 			indir;
	unsigned int	posit;

	if (cr->cycle->descript[0] == 2)
		cr->reg[cr->cycle->regs[1]] = get_param(cr, 0);
	else
	{
		indir = get_param(cr, 0);
		posit = check_position(cr->position + indir % IDX_MOD);
		from_memory_to_var(cr, &cr->reg[cr->cycle->regs[1]], posit, REG_SIZE);
	}
	if (!cr->reg[cr->cycle->regs[1]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("ld ");
}

void	st(t_carry *cr)
{
	short			indir;

	if (cr->cycle->descript[1] == 1)
		cr->reg[cr->cycle->regs[1]] = cr->reg[cr->cycle->regs[0]];
	else
	{
		indir = get_param(cr, 1);
		indir %= IDX_MOD;
		from_var_to_memory(cr, &cr->reg[cr->cycle->regs[0]], \
			check_position(cr->position + indir), REG_SIZE);
	}
	if (cr->vm->debug)
		ft_printf("st ");
}

void	add(t_carry *cr)
{
	cr->reg[cr->cycle->regs[2]] = cr->reg[cr->cycle->regs[0]] \
		+ cr->reg[cr->cycle->regs[1]];
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("add ");
}

void	sub(t_carry *cr)
{
	cr->reg[cr->cycle->regs[2]] = cr->reg[cr->cycle->regs[0]] \
		- cr->reg[cr->cycle->regs[1]];
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("sub ");
}

void	and(t_carry *cr)
{
	unsigned int	prm1;
	unsigned int	prm2;
	short 			indir;

	if (cr->cycle->descript[0] == 3)
	{
		indir = get_param(cr, 0);
		from_memory_to_var(cr, &prm1, check_position(cr->position +
		indir % IDX_MOD), REG_SIZE);
	}
	else
		prm1 = get_param(cr, 0);
	if (cr->cycle->descript[1] == 3)
	{
		indir = get_param(cr, 1);
		from_memory_to_var(cr, &prm2, check_position(cr->position +
		indir % IDX_MOD), REG_SIZE);
	}
	else
		prm2 = get_param(cr, 1);
	cr->reg[cr->cycle->regs[2]] = prm1 & prm2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("and ");
}

void	or(t_carry *cr)
{
	unsigned int	prm1;
	unsigned int	prm2;
	short 			indir;

	if (cr->cycle->descript[0] == 3)
	{
		indir = get_param(cr, 0);
		from_memory_to_var(cr, &prm1, check_position(cr->position +
		indir % IDX_MOD), REG_SIZE);
	}
	else
		prm1 = get_param(cr, 0);
	if (cr->cycle->descript[1] == 3)
	{
		indir = get_param(cr, 1);
		from_memory_to_var(cr, &prm2, check_position(cr->position +
		indir % IDX_MOD), REG_SIZE);
	}
	else
		prm2 = get_param(cr, 1);
	cr->reg[cr->cycle->regs[2]] = prm1 | prm2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("or ");
}

void	xor(t_carry *cr)
{
	unsigned int	prm1;
	unsigned int	prm2;
	short 			indir;

	if (cr->cycle->descript[0] == 3)
	{
		indir = get_param(cr, 0);
		from_memory_to_var(cr, &prm1, check_position(cr->position +
		indir % IDX_MOD), REG_SIZE);
	}
	else
		prm1 = get_param(cr, 0);
	if (cr->cycle->descript[1] == 3)
	{
		indir = get_param(cr, 1);
		from_memory_to_var(cr, &prm2, check_position(cr->position +
		indir % IDX_MOD), REG_SIZE);
	}
	else
		prm2 = get_param(cr, 1);
	cr->reg[cr->cycle->regs[2]] = prm1 ^ prm2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("xor ");
}


void	zjmp(t_carry *cr)
{
	short			dir;
	unsigned char	*src;
	unsigned char	*dst;

	if (!cr->carry)
		return ;
	dst = (unsigned char*)&dir;
	src = (unsigned char*)&cr->vm->area[check_position(cr->position + 1)];
	short_ind(dst, src);
	dir %= IDX_MOD;
	cr->position += dir;
	if (cr->position < 0)
		cr->position += MEM_SIZE;
	else if (cr->position >= MEM_SIZE)
		cr->position -= MEM_SIZE;
	cr->cycle->shift = 1;
	if (cr->vm->debug)
		ft_printf("zjmp ");
}

void	ldi(t_carry *cr)
{
	t_ldi		ldi;

	ft_bzero(&ldi, sizeof(ldi));
	if (cr->cycle->descript[0] == 1)
		get_param_plus(cr, &ldi.prm1, 0);
	else if (cr->cycle->descript[0] == 2)
		get_param_plus(cr, &ldi.dir1, 0);
	else
	{
		get_param_plus(cr, &ldi.indir, 0);
		from_memory_to_var(cr, &ldi.prm1, check_position(cr->position +
		ldi.indir % IDX_MOD), REG_SIZE);
	}
	if (cr->cycle->descript[1] == 1)
		get_param_plus(cr, &ldi.reg2, 1);
	else
		get_param_plus(cr, &ldi.dir2, 1);
	ldi.position = check_position(cr->position + \
		((ldi.prm1 + ldi.dir1 + ldi.dir2 + ldi.reg2) % IDX_MOD));
	from_memory_to_var(cr, &cr->reg[cr->cycle->regs[2]], ldi.position, REG_SIZE);
	if (cr->vm->debug)
		ft_printf("lti ");
}

void	sti(t_carry *cr)
{
	t_sti		sti;

	ft_bzero(&sti, sizeof(sti));
	get_param_plus(cr, &sti.reg1, 0);
	if (cr->cycle->descript[1] == 1)
		get_param_plus(cr, &sti.prm2, 1);
	else if (cr->cycle->descript[1] == 2)
		get_param_plus(cr, &sti.dir2, 1);
	else
	{
		get_param_plus(cr, &sti.indir, 1);
		from_memory_to_var(cr, &sti.prm2, check_position(cr->position +
		sti.indir % IDX_MOD), REG_SIZE);
	}
	if (cr->cycle->descript[2] == 1)
		get_param_plus(cr, &sti.reg3, 2);
	else
		get_param_plus(cr, &sti.dir3, 2);
	sti.position = check_position(cr->position + \
		((sti.prm2 + sti.dir2 + sti.dir3 + sti.reg3) % IDX_MOD));
	from_var_to_memory(cr, &sti.reg1, sti.position, REG_SIZE);
	if (cr->vm->debug)
		ft_printf("sti ");
}

static void	copy_carriage(t_carry *cr_src, short dir)
{
	t_carry	*cr;
	int		i;

	if (!(cr = ft_memalloc(sizeof(t_carry))))
		ft_error("Malloc couldn't allocate the memory!\n");
	i = 0;
	while (i < 16)
	{
		cr->reg[i] = cr_src->reg[i];
		i++;
	}
	cr->car_nbr = ++cr_src->vm->car_count;
	cr->position = dir;
	cr->vm = cr_src->vm;
	cr->carry = cr_src->carry;
	cr->last_live = cr_src->last_live;
	cr->color = cr_src->color;
	cr->next = cr->vm->carriages;
	cr->vm->carriages = cr;
}

void	frk(t_carry *cr)
{
	short			dir;
	unsigned char	*src;
	unsigned char	*dst;

	src = &cr->vm->area[check_position(cr->position + 1)];
	dst = (unsigned char*)&dir;
	if (ft_islitendian())
	{
		dst[1] = src[0];
		dst[0] = src[1];
	}
	else
	{
		dst[0] = src[0];
		dst[1] = src[1];
	}
	dir %= IDX_MOD;
	dir += cr->position;
	if (dir < 0)
		dir += MEM_SIZE;
	else if (dir >= MEM_SIZE)
		dir -= MEM_SIZE;
	copy_carriage(cr, dir);
	if (cr->vm->debug)
		ft_printf("frk ");
}

void	lld(t_carry *cr)
{
	short 			indir;
	unsigned int	posit;

	if (cr->cycle->descript[0] == 2)
		cr->reg[cr->cycle->regs[1]] = get_param(cr, 0);
	else
	{
		indir = get_param(cr, 0);
		posit = check_position(cr->position + indir);
		from_var_to_memory(cr, &cr->reg[cr->cycle->regs[1]], posit, REG_SIZE);
	}
	if (!cr->reg[cr->cycle->regs[1]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("lld ");
}

void	lldi(t_carry *cr)
{
	unsigned int	position;
	unsigned int	p1;
	unsigned int	p2;
	short 			indir;

	if (cr->cycle->descript[0] == 3)
	{
		indir = get_param(cr, 0);
		from_memory_to_var(cr, &p1, check_position(cr->position +
		indir % IDX_MOD), REG_SIZE);
	}
	else
		p1 = get_param(cr, 0);
	p2 = get_param(cr, 1);
	position = check_position(cr->position + (p1 + p2));
	from_memory_to_var(cr, &cr->reg[cr->cycle->regs[2]], position, REG_SIZE);
	if (cr->vm->debug)
		ft_printf("lldi ");
}

void	lfrk(t_carry *cr)
{
	short			dir;
	unsigned char	*src;
	unsigned char	*dst;

	src = &cr->vm->area[check_position(cr->position + 1)];
	dst = (unsigned char*)&dir;
	short_ind(dst, src);
	copy_carriage(cr, check_position(dir + cr->position));
	if (cr->vm->debug)
		ft_printf("frk ");
}

void	aff(t_carry *cr)
{
	char	prt;

	prt = (char)(cr->reg[cr->cycle->regs[0]]);
	if (cr->vm->a)
		write(1, &prt, 1);
	if (cr->vm->debug)
		ft_printf("aff ");
}

# include "vm.h"

void	live(t_carry *cr)
{
	unsigned int	dir;
	unsigned char	*ptr;
	int				i;
	int				*lala;

	cr->last_live = 0;
	cr->vm->live_counter++;
	ptr = (unsigned char*)&dir;
	i = 0;
	while (i < g_cmd_prms[cr->cmd_code - 1].dir_size)
	{
		ptr[i] = cr->vm->area[check_position(cr->position + 1 + i)];
		i++;
	}
	if (ft_islitendian())
		dir = ft_reverseint(dir);
	if (dir == cr->reg[0])
		cr->vm->last_alive = dir;
	lala = (int*)&dir;
	if (cr->vm->v)
		cr->vm->back[cr->position] |= 200;
	if (cr->vm->debug)
		ft_printf("alive! ");
}

void	ld(t_carry *cr)
{
	int				src_i;
	unsigned char	*dst;
	short			indir;

	src_i = check_position(cr->position + 2);
	if (cr->cycle->descript[0] == 3)
	{
		dst = (unsigned char*)&indir;
		if (cr->vm->l_endian)
		{
			dst[1] = cr->vm->area[src_i];
			dst[0] = cr->vm->area[check_position(src_i + 1)];
		}
		else
		{
			dst[1] = cr->vm->area[check_position(src_i + 1)];
			dst[0] = cr->vm->area[src_i];
		}
		src_i = indir_position(indir, cr);
	}
	dst = (unsigned char*)&cr->reg[cr->cycle->regs[1]];
	indir = 0;
	while (src_i < REG_SIZE)//endian??
	{
		dst[REG_SIZE - 1 - indir] = cr->vm->area[check_position(src_i)];
		indir++;
		src_i++;
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
	int 			src_i;
	unsigned char	*src;
	unsigned char	*dst;
	short			indir;
	int 			i;

	if (cr->cycle->descript[1] == 1)
		cr->reg[cr->cycle->regs[1]] = cr->reg[cr->cycle->regs[0]];
	else
	{
		src_i = check_position(cr->position + 3);
		dst = (unsigned char *)&indir;
		if (cr->vm->l_endian)
		{
			dst[1] = cr->vm->area[src_i];
			dst[0] = cr->vm->area[check_position((src_i) + 1)];
		}
		else
		{
			dst[0] = cr->vm->area[src_i];
			dst[1] = cr->vm->area[src_i + 1];
		}
		i = 0;
		src = (unsigned char *)&(cr->reg[cr->cycle->regs[0]]);
		indir = indir_position(indir, cr);
		while (i < REG_SIZE)
		{
			if (cr->vm->v)
				cr->vm->back[check_position(indir + i)] = cr->color - 1;
			cr->vm->area[check_position(indir + i)] = src[i];
			i++;
		}
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

	prm1 = get_param(cr, 0);
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

	prm1 = get_param(cr, 0);
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

	prm1 = get_param(cr, 0);
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
	int 			src_i;
	unsigned char	*dst;
	short			i;

	src_i = check_position(cr->position + (get_param(cr, 0) +
										   get_param(cr, 1)) % IDX_MOD);
	dst = (unsigned char*)&cr->reg[cr->cycle->regs[2]];
	i = 0;
	while (i < REG_SIZE)
	{
		dst[REG_SIZE - 1 - i] = cr->vm->area[check_position(src_i + i)];
		i++;
	}
	if (cr->vm->debug)
		ft_printf("ldi ");
}

//TODO: why sti's indir is incorrect, it has to be 16 in order to work properly

void	sti(t_carry *cr)
{
	unsigned char	*dst;
	unsigned char	*src;
	short			indir;
	int 			i;
	int 			src_i;

	src_i = check_position(cr->position + (get_param(cr, 1) + get_param3(cr)) % IDX_MOD);
	i = 0;
	dst = (unsigned char *)&indir;
	if (cr->vm->l_endian) //if it is npt a little_endian than it closer than it is now
	{
		dst[1] = cr->vm->area[src_i];
		dst[0] = cr->vm->area[check_position((src_i) + 1)];
	}
	else
	{
		dst[0] = cr->vm->area[src_i];
		dst[1] = cr->vm->area[check_position(src_i + 1)];
	}
	indir = indir_position(indir, cr);
	src = (unsigned char *)&(cr->reg[cr->cycle->regs[0]]);
	while (i < REG_SIZE)
	{
		if (cr->vm->v)
			cr->vm->back[check_position(indir + i)] = cr->color - 1;
		cr->vm->area[check_position(indir + i)] = src[i];
		i++;
	}
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
	unsigned char	*src;
	unsigned char	*dst;
	short			indir;

	src = &cr->vm->area[check_position(cr->position + 2)];
	if (cr->cycle->descript[0] == 3)
	{
		dst = (unsigned char*)&indir;
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
		indir += cr->position;
		if (indir < 0)
			indir += MEM_SIZE;
		else if (indir >= MEM_SIZE)
			indir -= MEM_SIZE;
		src = &cr->vm->area[indir];
	}
	dst = (unsigned char*)&cr->reg[cr->cycle->regs[1]];
	indir = 0;
	while (indir < REG_SIZE)
	{
		dst[REG_SIZE - 1 - indir] = src[indir];
		indir++;
	}
	if (!cr->reg[cr->cycle->regs[1]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("ld ");
}

void	lldi(t_carry *cr)
{
	unsigned char	*src;
	unsigned char	*dst;
	short			i;

	src = &cr->vm->area[check_position(cr->position + (get_param(cr, 0) +
					 get_param(cr, 1)))];
	dst = (unsigned char*)&cr->reg[cr->cycle->regs[2]];
	i = 0;
	while (i < REG_SIZE)
	{
		dst[REG_SIZE - 1 - i] = src[i];
		i++;
	}
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
	ft_printf("%c", (char)(cr->reg[cr->cycle->regs[0]]));
	if (cr->vm->debug)
		ft_printf("aff ");
}

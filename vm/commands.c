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
		ptr[i] = cr->vm->area[cr->position + 1 + i];
		i++;
	}
	if (ft_islitendian())
		dir = ft_reverseint(dir);
	if (dir == cr->reg[0])
		cr->vm->last_alive = dir;
	lala = (int*)&dir;
	ft_printf("alive! ");
}

void	ld(t_carry *cr)
{
	unsigned char	*src;
	unsigned char	*dst;
	short			indir;

	src = &cr->vm->area[cr->position + 2];
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
		indir %= IDX_MOD;
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
	ft_printf("ld ");
}

void	st(t_carry *cr)
{
	unsigned char	*dst;
	unsigned char	*src;
	short			indir;
	int 			i;

	if (cr->cycle->descript[1] == 1)
		cr->reg[cr->cycle->regs[1]] = cr->reg[cr->cycle->regs[0]];
	else
	{
		i = 0;
		src = &cr->vm->area[cr->position + 3];
		dst = (unsigned char *)&indir;
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
		indir %= IDX_MOD;
		indir += cr->position;
		if (indir < 0)
			indir += MEM_SIZE;
		else if (indir >= MEM_SIZE)
			indir -= MEM_SIZE;
		src = (unsigned char *)&(cr->reg[cr->cycle->regs[0]]);
		while (i < REG_SIZE)
		{
			cr->vm->area[indir + i] = src[i];
			i++;
		}
	}
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
	ft_printf("sub ");
}
/*
** Is there any check that in and operation first and second argument would be
** the same type?
*/
void	and(t_carry *cr)
{
	unsigned int	dir1;
	unsigned int	dir2;
	int 			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (cr->cycle->descript[0] == 1 && cr->cycle->descript[1] == 1)
		cr->reg[cr->cycle->descript[2]] = cr->reg[cr->cycle->descript[0]] &
				cr->reg[cr->cycle->descript[1]];
	else if (cr->cycle->descript[0] == 2 && cr->cycle->descript[1] == 2)
	{
		i = 0;
		ptr1 = (unsigned char *)&dir1;
		ptr2 = (unsigned char *)&dir2;
		while (i < g_cmd_prms[cr->cmd_code - 1].dir_size)
		{
			ptr1[i] = cr->vm->area[cr->position + 1 + i];
			ptr2[i] = cr->vm->area[cr->position + 5 + i];
			i++;
		}
		if (ft_islitendian())
		{
			dir1 = ft_reverseint(dir1);
			dir2 = ft_reverseint(dir2);
		}
		cr->reg[cr->cycle->descript[2]] = dir1 & dir2;
	}
	else if (cr->cycle->descript[0] == 3 && cr->cycle->descript[1] == 3)
	{

	}
	ft_printf("and ");
}

void	or(t_carry *cr)
{
	ft_printf("or ");
}

void	xor(t_carry *cr)
{
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
	src = (unsigned char*)&cr->vm->area[cr->position + 1];
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
	cr->position += dir;
	if (cr->position < 0)
		cr->position += MEM_SIZE;
	else if (cr->position >= MEM_SIZE)
		cr->position -= MEM_SIZE;
	cr->cycle->shift = 1;
	ft_printf("zjmp ");
}

void	ldi(t_carry *cr)
{
	ft_printf("ldi ");
}

void	sti(t_carry *cr)
{
	// ft_printf("car %u on %d: sti\tcycle: %u\n", cr->car_nbr, cr->position, \
	// 	vm->cycles_from_start);
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

	src = &cr->vm->area[cr->position + 1];
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
	ft_printf("frk ");
}

void	lld(t_carry *cr)
{
	ft_printf("lld ");
}

void	lldi(t_carry *cr)
{
	ft_printf("lldi ");
}

void	lfrk(t_carry *cr)
{
	short			dir;
	unsigned char	*src;
	unsigned char	*dst;

	src = &cr->vm->area[cr->position + 1];
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
	dir += cr->position;
	if (dir < 0)
		dir += MEM_SIZE;
	else if (dir >= MEM_SIZE)
		dir -= MEM_SIZE;
	copy_carriage(cr, dir);
	ft_printf("frk ");
}

void	aff(t_carry *cr)
{
	ft_printf("%c", (char)(cr->reg[cr->cycle->regs[0]]));
	ft_printf("aff ");
}

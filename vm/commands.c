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
		dst[1] = src[0];
		dst[0] = src[1];
		indir %= IDX_MOD;
		src = &cr->vm->area[cr->position + indir];
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

void	and(t_carry *cr)
{
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
	dst[1] = src[0];
	dst[0] = src[1];
	dir %= IDX_MOD;
	cr->position += dir;
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

void	frk(t_carry *cr)
{
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
	ft_printf("lfrk ");
}

void	aff(t_carry *cr)
{
	ft_printf("aff ");
}

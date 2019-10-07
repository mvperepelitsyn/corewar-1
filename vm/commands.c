# include "vm.h"

void	live(t_vm *vm, t_carry *cr)
{
	unsigned int	dir;
	unsigned char	*ptr;
	int				i;
	static int		l;

	cr->last_live = 0;
	vm->live_counter++;
	ptr = (unsigned char*)&dir;
	i = 0;
	while (i < g_cmd_prms[cr->cmd_code - 1].dir_size)
	{
		ptr[i] = vm->area[cr->position + 1 + i];
		i++;
	}
	if (ft_islitendian())
		dir = ft_reverseint(dir);
	if (dir == cr->reg[0])
		vm->last_alive = dir;
	l++;
	ft_printf("alive! ");
}

void	ld(t_vm *vm, t_carry *cr)
{
	ft_printf("ld ");
}

void	st(t_vm *vm, t_carry *cr)
{
	ft_printf("st ");
}

void	add(t_vm *vm, t_carry *cr)
{
	ft_printf("add ");
}

void	sub(t_vm *vm, t_carry *cr)
{
	ft_printf("sub ");
}

void	and(t_vm *vm, t_carry *cr)
{
	ft_printf("and ");
}

void	or(t_vm *vm, t_carry *cr)
{
	ft_printf("or ");
}

void	xor(t_vm *vm, t_carry *cr)
{
	ft_printf("xor ");
}

void	zjmp(t_vm *vm, t_carry *cr)
{
	ft_printf("zjmp ");
}

void	ldi(t_vm *vm, t_carry *cr)
{
	ft_printf("ldi ");
}

void	sti(t_vm *vm, t_carry *cr)
{
	ft_printf("car %u on %d: sti\tcycle: %u\n", cr->car_nbr, cr->position, \
		vm->cycles_from_start);
}

void	frk(t_vm *vm, t_carry *cr)
{
	ft_printf("frk ");
}

void	lld(t_vm *vm, t_carry *cr)
{
	ft_printf("lld ");
}

void	lldi(t_vm *vm, t_carry *cr)
{
	ft_printf("lldi ");
}

void	lfrk(t_vm *vm, t_carry *cr)
{
	ft_printf("lfrk ");
}

void	aff(t_vm *vm, t_carry *cr)
{
	ft_printf("aff ");
}

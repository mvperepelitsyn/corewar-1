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
	ft_printf("alive!\n");
}

void	ld(t_vm *vm, t_carry *cr)
{
	ft_printf("ld\n");
}

void	st(t_vm *vm, t_carry *cr)
{
	ft_printf("st\n");
}

void	add(t_vm *vm, t_carry *cr)
{
	ft_printf("add\n");
}

void	sub(t_vm *vm, t_carry *cr)
{
	ft_printf("sub\n");
}

void	and(t_vm *vm, t_carry *cr)
{
	ft_printf("and\n");
}

void	or(t_vm *vm, t_carry *cr)
{
	ft_printf("or\n");
}

void	xor(t_vm *vm, t_carry *cr)
{
	ft_printf("xor\n");
}

void	zjmp(t_vm *vm, t_carry *cr)
{
	ft_printf("zjmp\n");
}

void	ldi(t_vm *vm, t_carry *cr)
{
	ft_printf("ldi\n");
}

void	sti(t_vm *vm, t_carry *cr)
{
	ft_printf("car %u on %d: sti\tcycle: %u\n", cr->car_nbr, cr->position, \
		vm->cycles_from_start);
}

void	frk(t_vm *vm, t_carry *cr)
{
	ft_printf("frk\n");
}

void	lld(t_vm *vm, t_carry *cr)
{
	ft_printf("lld\n");
}

void	lldi(t_vm *vm, t_carry *cr)
{
	ft_printf("lldi\n");
}

void	lfrk(t_vm *vm, t_carry *cr)
{
	ft_printf("lfrk\n");
}

void	aff(t_vm *vm, t_carry *cr)
{
	ft_printf("aff\n");
}

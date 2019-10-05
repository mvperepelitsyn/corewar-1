# include "vm.h"

void	live(t_vm *vm, t_carry *cr)
{
	unsigned int	dir;
	unsigned char	*ptr;
	int				i;

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
}

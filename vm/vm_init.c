# include "vm.h"

static void	area_init(t_vm *vm)
{
	int		champ_area;
	int		champ_nbr;
	int		i;
	int		j;

	champ_area = MEM_SIZE / vm->champs_count;
	champ_nbr = 0;
	if (!(vm->area = ft_memalloc(MEM_SIZE)))
		ft_error("Malloc couldn't allocate the memory!\n");
	while (champ_nbr < vm->champs_count)
	{
		i = champ_area * champ_nbr;
		j = 0;
		while (j < vm->processes[champ_nbr].code_size)
		{
			vm->area[i] = vm->processes[champ_nbr].code[j];
			i++;
			j++;
		}
		champ_nbr++;
	}
}

void		vm_init(t_vm *vm)
{
	vm->command[0] = &live;
	vm->command[1] = &ld;
	vm->command[2] = &st;
	vm->command[3] = &add;
	vm->command[4] = &sub;
	vm->command[5] = &and;
	vm->command[6] = &or;
	vm->command[7] = &xor;
	vm->command[8] = &zjmp;
	vm->command[9] = &ldi;
	vm->command[10] = &sti;
	vm->command[11] = &frk;
	vm->command[12] = &lld;
	vm->command[13] = &lldi;
	vm->command[14] = &lfrk;
	vm->command[15] = &aff;
	area_init(vm);
}

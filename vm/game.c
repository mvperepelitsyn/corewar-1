# include "vm.h"

static void	print_game_area()
{
	//
}

static void	check_game(t_vm *vm)
{
	//
}

static void	cycle(t_vm *vm)
{
	//
}

void		game(t_vm *vm)
{
	while(vm->carriages || (vm->dump && vm->cycles_from_start < vm->dump))
	{
		cycle(vm);
		if (vm->ctd_counter == vm->cycles_to_die)
		{
			check_game(vm);
			vm->ctd_counter = 0;
		}
	}
	if (vm->dump && vm->carriages)
		print_game_area();
	else
		ft_printf("Contestant %d, \"%s\", has won!\n", (int)vm->last_alive, \
			vm->processes[vm->last_alive - 1].cmp_name);
}

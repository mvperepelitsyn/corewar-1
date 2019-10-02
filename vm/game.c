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
	t_carry	*cr;

	cr = vm->carriages;
	while (cr)
	{
		if (!cr->cycles_before)
		{
			cr->reg[0] = vm->area[cr->position];
			if (vm->area[cr->position] >= 1 && vm->area[cr->position] <= 16)
				cr->cycles_before = vm->cmd_prms[cr->reg[0]].cycles_before;
		}
		if (cr->cycles_before)
			cr->cycles_before--;
		if (!cr->cycles_before/* valid check! */)
			vm->command[cr->reg[0] - 1](vm, cr);
		/*else
			move carreage to "calc" bytes count
		*/
		//
		cr = cr->next;
	}
}

void		game(t_vm *vm)
{
	while (vm->carriages || (vm->dump && vm->cycles_from_start < vm->dump))
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
		ft_printf("Contestant %uhh, \"%s\", has won !\n", vm->last_alive, \
			vm->processes[vm->last_alive - 1].cmp_name);
}

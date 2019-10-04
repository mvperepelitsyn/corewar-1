# include "vm.h"

static void	print_game_area()
{
	//
}

static void	check_game(t_vm *vm)
{
	//
}

//static int	check_operation(t_vm *vm, t_carry *cr)
//{
//	if (!(cr->cmd_code >= 1 && cr->cmd_code <= 16))
//		return (0);
//
//	return(1);
//}

static void	cycle(t_vm *vm)
{
	t_carry	*cr;
	t_cycle	cycle;

	cr = vm->carriages;
	while (cr)
	{
		if (!cr->cycles_before)
		{
			cr->cmd_code = vm->area[cr->position];
			if (cr->cmd_code >= 1 && cr->cmd_code <= 16)
				cr->cycles_before = g_cmd_prms[cr->cmd_code].cycles_before;
		}
		if (cr->cycles_before)
			cr->cycles_before--;
		cr->jump_len = 1;
		if (!cr->cycles_before && check_operation(vm, cr, &cycle))
			vm->command[cr->reg[0] - 1](vm, cr);
		cr->position += cr->jump_len;
		if (cr->position >= MEM_SIZE)
			cr->position -= MEM_SIZE;
		else if (cr->position < 0)
			cr->position += MEM_SIZE;
		cr = cr->next;
	}
}

void		game(t_vm *vm)
{
	while (vm->carriages || (vm->dump && vm->cycles_from_start < vm->dump))
	{
		cycle(vm);
		vm->cycles_from_start++;
		vm->ctd_counter++;
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

# include "vm.h"

static void	print_game_area()
{
	//
}

static void	carriage_remover(t_vm *vm, t_carry *prev, t_carry *cur)
{
	t_carry	*ptr;

	if (!prev)
	{
		vm->carriages = cur->next;
		free(cur);
		return ;
	}
	ptr = cur->next;
	free(cur);
	prev->next = ptr;
}

static void	check_game(t_vm *vm)
{
	t_carry *prev;
	t_carry *cur;
	t_carry *next;

	prev = NULL;
	if (vm->cycles_to_die <= 0)
		while (vm->carriages)
			carriage_remover(vm, prev, vm->carriages);
	cur = vm->carriages;
	while (cur)
	{
		next = cur->next;
		if (cur->last_live >= vm->cycles_to_die)
		{
			carriage_remover(vm, prev, cur);
			cur = next;
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
	vm->cycles_to_die -= CYCLE_DELTA;
}

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
		cr->last_live++;
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
		if (vm->ctd_counter == vm->cycles_to_die || vm->cycles_to_die <= 0)
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

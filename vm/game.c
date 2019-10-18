# include "vm.h"
// #include <stdio.h>

static void	carriage_remover(t_vm *vm, t_carry *prev, t_carry *cur)
{
	t_carry	*ptr;

	if (!prev)
	{
		vm->carriages = cur->next;
		free(cur);
	if (vm->debug)
		ft_printf("remove!\n");
		return ;
	}
	ptr = cur->next;
	free(cur);
	prev->next = ptr;
	if (vm->debug)
		ft_printf("remove!\n");
}

static void	check_game(t_vm *vm)
{
	t_carry *prev;
	t_carry *cur;
	t_carry *next;

	// ft_printf("check game cycle: %u\t ctd_counter: %d\n", vm->cycles_from_start, \
	// 	vm->ctd_counter);
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
	if (vm->live_counter >= NBR_LIVE || vm->check_counter >= MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->check_counter = 0;
	}
	else
		vm->check_counter++;
	vm->live_counter = 0;
}

static void	cycle(t_vm *vm)
{
	t_carry	*cr;
	t_cycle	cycle;

	cr = vm->carriages;
	while (cr)
	{
		ft_bzero((void*)&cycle, sizeof(cycle));
		cr->cycle = &cycle;
		if (!cr->cycles_before)
		{
			cr->cmd_code = vm->area[cr->position];
			if (cr->cmd_code >= 1 && cr->cmd_code <= 16)
				cr->cycles_before = g_cmd_prms[cr->cmd_code - 1].cycles_before;
		}
		if (cr->cycles_before)
			cr->cycles_before--;
		if (!cr->cycles_before)
		{
			cr->jump_len = 1;
			if (check_operation(vm, cr, &cycle))
				vm->command[cr->cmd_code - 1](cr);
			if (!cycle.shift)
				cr->position = check_position(cr->position + cr->jump_len);
		}
		cr->last_live++;
		cr = cr->next;
	}
}

void		game(t_vm *vm)
{
	vm->debug = 0;
	if (vm->dump_flag && !vm->dump)
	{
		if (vm->v)
			game_area_frame(vm);
		else
			print_game_area(vm);
		return ;
	}
	while (vm->carriages)
	{
		cycle(vm);
		vm->cycles_from_start += 1;
		vm->ctd_counter += 1;
		if (vm->v && !vm->dump)
			game_area_frame(vm);
		if (vm->ctd_counter >= vm->cycles_to_die || vm->cycles_to_die <= 0)
		{
			check_game(vm);
			vm->ctd_counter = 0;
		}
		if (vm->dump && vm->cycles_from_start >= vm->dump)
			break ;
	}
	if (vm->dump && vm->carriages)
	{
		if (vm->v)
			game_area_frame(vm);
		else
			print_game_area(vm);
	}
	else
		ft_printf("Contestant %u, \"%s\", has won !\n", \
			((int)vm->last_alive * -1), \
			vm->processes[((int)vm->last_alive * -1) - 1].cmp_name);
}

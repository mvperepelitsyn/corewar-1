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

void debug()
{
	//
}

static void	cycle(t_vm *vm)
{
	t_carry	*cr;
	t_cycle	cycle;

	cr = vm->carriages;
	if (vm->cycles_from_start == 304)
		vm->cycles_from_start = 304;
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
			if (cr->cmd_code == 9)
				debug();
			if (check_operation(vm, cr, &cycle))
				vm->command[cr->cmd_code - 1](cr);
			if (!cycle.shift)
			{
				cr->position += cr->jump_len;
				if (cr->position >= MEM_SIZE)
					cr->position -= MEM_SIZE;
				else if (cr->position < 0)
					cr->position += MEM_SIZE;
			}
		}
		cr->last_live++;
		cr = cr->next;
	}
}

void		game(t_vm *vm)
{
	// print_game_area(vm);
	// exit(0);
	// ft_printf("%u\n", vm->dump);
	vm->debug = 0;
	// if (vm->v)
	// 	game_area_frame(vm);
	while (vm->carriages)
	{
		cycle(vm);

		if (vm->v)
			game_area_frame(vm);
		vm->cycles_from_start++;
		vm->ctd_counter++;
		if (vm->ctd_counter == vm->cycles_to_die || vm->cycles_to_die <= 0)
		{
			// ft_printf("lala! ");
			check_game(vm);
			vm->ctd_counter = 0;
		}
		if (vm->dump && vm->cycles_from_start >= vm->dump)
			break ;
		// ft_printf("%u ", vm->cycles_from_start);
	}
	ft_printf("\n");
	// print_game_area(vm);
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

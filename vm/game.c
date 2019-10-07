# include "vm.h"

static void	print_game_area(t_vm *vm)
{
	unsigned int	byte;

	byte = 0;
	while (byte < MEM_SIZE)
	{
		if (byte)
			ft_printf("%#06x : ", byte);
		else
			ft_printf("0x0000 : ");
		while (byte % 32 < 31)
		{
			ft_printf("%02x ", (unsigned int)vm->area[byte]);
			byte++;
		}
		ft_printf("%02x\n", (unsigned int)vm->area[byte]);
		byte++;
	}
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
	// ft_printf("ctd: %d | ", vm->cycles_to_die);
	while (cur)
	{
		next = cur->next;
		// ft_printf("\tcar: %u, last_live: %d", cur->car_nbr, cur->last_live);
		if (cur->last_live >= vm->cycles_to_die)
		{
			carriage_remover(vm, prev, cur);
			cur = next;
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
	// ft_printf("\n");
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
		if (!cr->cycles_before)
		{
			cr->cmd_code = vm->area[cr->position];
			// ft_printf("% hhu ", cr->cmd_code);
			if (cr->cmd_code >= 1 && cr->cmd_code <= 16)
				cr->cycles_before = g_cmd_prms[cr->cmd_code - 1].cycles_before;
		}
		if (cr->cycles_before)
			cr->cycles_before--;
		if (!cr->cycles_before)
		{
			cr->jump_len = 1;
			if (check_operation(vm, cr, &cycle))
				vm->command[cr->cmd_code - 1](vm, cr);
			cr->position += cr->jump_len;
			if (cr->position >= MEM_SIZE)
				cr->position -= MEM_SIZE;
			else if (cr->position < 0)
				cr->position += MEM_SIZE;
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
	while (vm->carriages)
	{
		cycle(vm);
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
	if (vm->dump && vm->carriages)
		print_game_area(vm);
	else
		ft_printf("Contestant %hhu, \"%s\", has won !\n", vm->last_alive, \
			vm->processes[vm->last_alive - 1].cmp_name);
}

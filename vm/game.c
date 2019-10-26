/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:24:16 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/21 20:24:18 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

static void	help_check_game(t_vm *vm)
{
	if (vm->live_counter >= NBR_LIVE || vm->check_counter >= MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->check_counter = 0;
		if (vm->verbose.v && vm->verbose.v_2)
			ft_printf("Cycle to die now is %d\n", vm->cycles_to_die);
	}
	else
		vm->check_counter++;
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
	help_check_game(vm);
	vm->live_counter = 0;
}

static void	help_game(t_vm *vm)
{
	while (vm->carriages)
	{
		if (vm->cycles_from_start == 30218)
			vm->cycles_from_start = 30218;
		cycle(vm);
		vm->cycles_from_start++;
		if (vm->verbose.v && vm->verbose.v_2)
			ft_printf("It is now cycle %d\n", vm->cycles_from_start);
		vm->ctd_counter++;
		if (vm->vis && !vm->dump)
			game_area_frame(vm);
		if (vm->ctd_counter >= vm->cycles_to_die || vm->cycles_to_die <= 0)
		{
			check_game(vm);
			vm->ctd_counter = 0;
		}
		if (vm->dump && vm->cycles_from_start >= vm->dump)
			break ;
	}
}

void		game(t_vm *vm)
{
	vm->debug = 0;
	if (vm->dump_flag && !vm->dump)
	{
		if (vm->vis)
			game_area_frame(vm);
		else
			print_game_area(vm);
		return ;
	}
	help_game(vm);
	if (vm->dump && vm->carriages)
	{
		if (vm->vis)
			game_area_frame(vm);
		else
			print_game_area(vm);
	}
	else
		ft_printf("Contestant %u, \"%s\", has won !\n", \
			((int)vm->last_alive * -1), \
			vm->processes[((int)vm->last_alive * -1) - 1].cmp_name);
}

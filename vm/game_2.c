/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:53:32 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/28 18:03:39 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	help_cycle(t_vm *vm, t_carry *cr, t_cycle *cycle)
{
	if (!cr->cycles_before)
	{
		cr->jump_len = 1;
		if (check_operation(vm, cr, cycle))
			vm->command[cr->cmd_code - 1](cr);
		if (!(*cycle).shift)
			cr->position = check_position(cr->position + cr->jump_len);
	}
}

// static void		debug()
// {
// 	//
// }

void		cycle(t_vm *vm)
{
	t_carry	*cr;
	t_cycle	cycle;

	cr = vm->carriages;
	while (cr)
	{
		ft_bzero((void*)&cycle, sizeof(cycle));
		cr->cycle = &cycle;
		// if (vm->cycles_from_start == 26493)
		// 	debug();
		if (!cr->cycles_before)
		{
			cr->cmd_code = vm->area[cr->position];
			if (cr->cmd_code >= 1 && cr->cmd_code <= 16)
				cr->cycles_before = g_cmd_prms[cr->cmd_code - 1].cycles_before;
		}
		if (cr->cycles_before)
			cr->cycles_before--;
		help_cycle(vm, cr, &cycle);
		cr->last_live++;
		cr = cr->next;
	}
}

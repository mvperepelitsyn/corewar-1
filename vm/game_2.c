/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:53:32 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/28 18:07:45 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	help_cycle(t_vm *vm, t_carry *cr, t_cycle *cycle)
{
	int 	h_ps;

	h_ps = 0;
	if (!cr->cycles_before)
	{
		cr->jump_len = 1;
		if (check_operation(vm, cr, cycle))
			vm->command[cr->cmd_code - 1](cr);
		if (!(*cycle).shift)
		{
			h_ps = cr->position + cr->jump_len;
			if (vm->verbose.v && vm->verbose.v_16 && cr->jump_len > 1)//vm->area[cr->position])
			{
				if (cr->position == 0 && h_ps != 0)
					ft_printf("ADV %d (0x0000 -> %#06x) ", cr->jump_len, h_ps);
				else if (cr->position != 0 && h_ps == 0)
					ft_printf("ADV %d (%#06x -> 0x0000) ", cr->jump_len, cr->
					position);
				else
					ft_printf("ADV %d (%#06x -> %#06x) ", cr->jump_len, cr->
					position, h_ps);
				h_ps = check_position(h_ps);
				while (cr->position != h_ps)
				{
					ft_printf("%02x ", (unsigned int)vm->area[check_position(
							cr->position)]);
					cr->position = check_position(cr->position + 1);
				}
				ft_putchar('\n');
			}
			else
				cr->position = check_position(h_ps);
		}
	}
}

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

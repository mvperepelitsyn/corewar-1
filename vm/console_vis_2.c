/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_vis_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:36:33 by uhand             #+#    #+#             */
/*   Updated: 2019/10/30 18:39:23 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	report_norm(t_vm *vm, t_carry *cr)
{
	ft_printf("%5d: ", cr->car_nbr);
	if (cr->last_champ)
		ft_printf("%s \"Champion\" (%d) said \"Alive!\" %d cycles ago (%u)."
			"\t", vm->processes[(cr->last_champ * -1) - 1].cmp_name, \
			cr->last_champ, cr->last_live, cr->last_alive_cycle);
	else
		ft_printf("UNKNOWN\t\t\t  said \"Alive!\" %d cycles ago (%u).\t", \
			cr->last_live, cr->last_alive_cycle);
	if (cr->cmd_code >= 1 && cr->cmd_code <= 16 \
			&& !(vm->dump_flag && !vm->dump))
		ft_printf("\tNext command: \"%s\" in %u cycles\n", \
			g_cmd_prms[cr->cmd_code - 1].name, cr->cycles_before);
	else if (!(vm->dump_flag && !vm->dump))
		ft_printf("\tWrong command code: %hhu\n", cr->cmd_code);
}

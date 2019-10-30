/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:31:54 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/30 14:31:56 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	sti_verbose_print(t_carry *cr, t_sti *sti)
{
	ft_printf("P%*d | sti r%d %d %d\n       | -> store to %d + %d = %d (with pc"
" and mod %d)\n", ((ft_hw_mn_orders(cr->car_nbr) < 5) ? 5 : ft_hw_mn_orders(cr->
car_nbr) + 1), cr->car_nbr, cr->cycle->regs[0] + 1, sti->dir2 + sti->prm2, sti->
dir3 + sti->reg3, sti->dir2 + sti->prm2, sti->dir3 + sti->reg3, sti->prm2 +
sti->dir2 + sti->dir3 + sti->reg3, sti->position);
}

void		sti(t_carry *cr)
{
	t_sti		sti;

	ft_bzero(&sti, sizeof(sti));
	get_param_plus(cr, &sti.reg1, 0);
	if (cr->cycle->descript[1] == 1)
		get_param_plus(cr, &sti.prm2, 1);
	else if (cr->cycle->descript[1] == 2)
		get_param_plus(cr, &sti.dir2, 1);
	else
	{
		get_param_plus(cr, &sti.indir, 1);
		from_memory_to_var(cr, &sti.prm2, check_position(cr->position +
		sti.indir % IDX_MOD), REG_SIZE);
	}
	if (cr->cycle->descript[2] == 1)
		get_param_plus(cr, &sti.reg3, 2);
	else
		get_param_plus(cr, &sti.dir3, 2);
	sti.position = cr->position + \
		((sti.prm2 + sti.dir2 + sti.dir3 + sti.reg3) % IDX_MOD);
	from_var_to_memory(cr, &sti.reg1, check_position(sti.position), REG_SIZE);
	if (cr->vm->verbose.v && cr->vm->verbose.v_4)
		sti_verbose_print(cr, &sti);
	if (cr->vm->debug)
		ft_printf("sti ");
}

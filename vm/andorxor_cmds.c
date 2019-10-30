/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andorxor_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:49:20 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/22 12:49:23 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		and(t_carry *cr)
{
	t_andorxor	aox;

	ft_bzero(&aox, sizeof(aox));
	if (cr->cycle->descript[0] == 3)
	{
		aox.indir = get_param(cr, 0);
		from_memory_to_var(cr, &aox.prm1, check_position(cr->position +
		aox.indir % IDX_MOD), REG_SIZE);
	}
	else
		aox.prm1 = get_param(cr, 0);
	if (cr->cycle->descript[1] == 3)
	{
		aox.indir = get_param(cr, 1);
		from_memory_to_var(cr, &aox.prm2, check_position(cr->position +
		aox.indir % IDX_MOD), REG_SIZE);
	}
	else
		aox.prm2 = get_param(cr, 1);
	cr->reg[cr->cycle->regs[2]] = aox.prm1 & aox.prm2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->verbose.v && cr->vm->verbose.v_4)
		ft_printf("P%*d | and %d %d r%d\n", ((ft_hw_mn_orders(cr->car_nbr) < 5)
		? 5 : ft_hw_mn_orders(cr->car_nbr) + 1), cr->car_nbr, aox.prm1, aox.
		prm2, cr->cycle->regs[2] + 1);
	if (cr->vm->debug)
		ft_printf("and ");
}

void		or(t_carry *cr)
{
	t_andorxor	aox;

	ft_bzero(&aox, sizeof(aox));
	if (cr->cycle->descript[0] == 3)
	{
		aox.indir = get_param(cr, 0);
		from_memory_to_var(cr, &aox.prm1, check_position(cr->position +
		aox.indir % IDX_MOD), REG_SIZE);
	}
	else
		aox.prm1 = get_param(cr, 0);
	if (cr->cycle->descript[1] == 3)
	{
		aox.indir = get_param(cr, 1);
		from_memory_to_var(cr, &aox.prm2, check_position(cr->position +
		aox.indir % IDX_MOD), REG_SIZE);
	}
	else
		aox.prm2 = get_param(cr, 1);
	cr->reg[cr->cycle->regs[2]] = aox.prm1 | aox.prm2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->verbose.v && cr->vm->verbose.v_4)
		ft_printf("P%*d | or %d %d r%d\n", ((ft_hw_mn_orders(cr->car_nbr) < 5) ?
		5 : ft_hw_mn_orders(cr->car_nbr) + 1), cr->car_nbr, aox.prm1, aox.prm2,
				  cr->cycle->regs[2] + 1);
	if (cr->vm->debug)
		ft_printf("or ");
}

void		xor(t_carry *cr)
{
	t_andorxor		aox;

	ft_bzero(&aox, sizeof(aox));
	if (cr->cycle->descript[0] == 3)
	{
		aox.indir = get_param(cr, 0);
		from_memory_to_var(cr, &aox.prm1, check_position(cr->position +
		aox.indir % IDX_MOD), REG_SIZE);
	}
	else
		aox.prm1 = get_param(cr, 0);
	if (cr->cycle->descript[1] == 3)
	{
		aox.indir = get_param(cr, 1);
		from_memory_to_var(cr, &aox.prm2, check_position(cr->position +
		aox.indir % IDX_MOD), REG_SIZE);
	}
	else
		aox.prm2 = get_param(cr, 1);
	cr->reg[cr->cycle->regs[2]] = aox.prm1 ^ aox.prm2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->verbose.v && cr->vm->verbose.v_4)
		ft_printf("P%*d | xor %d %d r%d\n", ((ft_hw_mn_orders(cr->car_nbr) < 5)
		? 5 : ft_hw_mn_orders(cr->car_nbr) + 1), cr->car_nbr, aox.prm1, aox.
		prm2, cr->cycle->regs[2] + 1);
	if (cr->vm->debug)
		ft_printf("xor ");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:25:43 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/28 21:09:26 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		live(t_carry *cr)
{
	unsigned int dir;
	int *champ_nbr;

	cr->last_live = 0;
	cr->vm->live_counter++;
	dir = get_param(cr, 0);
	champ_nbr = (int *) &dir;
	if (cr->vm->verbose.v_4)
		ft_printf("P    %d | live %d\n", cr->car_nbr, dir);
	if ((champ_nbr[0] * -1) > 0 \
 && (champ_nbr[0] * -1) <= (int) cr->vm->champs_count)
	{
		// cr->vm->live_counter++;//
		cr->vm->last_alive = dir;
		cr->last_champ = dir;
		cr->last_alive_cycle = cr->vm->cycles_from_start + 1;
		cr->vm->last_alive_cycle = cr->vm->cycles_from_start + 1;
		if (cr->vm->verbose.v_1)
			ft_printf("Player %d (%s) is said to be alive\n", cr->vm->last_alive
			* -1, cr->vm->processes[cr->vm->last_alive * -1 - 1].cmp_name);
	}
	if (cr->vm->vis)
		cr->vm->back[cr->position] |= 200;
//	if (cr->vm->verbose.v)
//	{
//		if (cr->vm->verbose.v_4)
//			ft_printf("P    %d | live %d\n", cr->car_nbr, dir);
//		if (cr->vm->verbose.v_1)
//			ft_printf("Player %d (%s) is said to be alive\n", cr->vm->last_alive
//			* -1, cr->vm->processes[cr->vm->last_alive * -1 - 1].cmp_name);
//	}
	if (cr->vm->debug)
	{
		ft_printf("%d ", champ_nbr[0]);
		ft_printf("alive %d! ", cr->vm->last_alive);
	}
}

static void	copy_carriage(t_carry *cr_src, short dir)
{
	t_carry	*cr;
	int		i;

	if (!(cr = ft_memalloc(sizeof(t_carry))))
		ft_error("Malloc couldn't allocate the memory!\n");
	i = 0;
	while (i < 16)
	{
		cr->reg[i] = cr_src->reg[i];
		i++;
	}
	cr->car_nbr = ++cr_src->vm->car_count;
	cr->position = dir;
	cr->vm = cr_src->vm;
	cr->carry = cr_src->carry;
	cr->last_live = cr_src->last_live + 1;
	cr->color = cr_src->color;
	cr->next = cr->vm->carriages;
	cr->vm->carriages = cr;
}

void		frk(t_carry *cr)
{
	short			dir;
	short 			dir_hlp;

	get_param_plus(cr, &dir_hlp, 0);
	dir = dir_hlp % IDX_MOD;
	dir = cr->position + dir;
	copy_carriage(cr, check_position(dir));
	if (cr->vm->verbose.v && cr->vm->verbose.v_4)
		ft_printf("P    %d | fork %d (%d)\n", cr->car_nbr, dir_hlp, dir);
	if (cr->vm->debug)
		ft_printf("frk ");
}

void		lfrk(t_carry *cr)
{
	short			dir;

	get_param_plus(cr, &dir, 0);
	dir = check_position(cr->position + dir);
	copy_carriage(cr, dir);
	if (cr->vm->verbose.v && cr->vm->verbose.v_4)
		ft_printf("P    %d | lfork -%d (%d)\n", cr->car_nbr, cr->cmd_code, dir);
	if (cr->vm->debug)
		ft_printf("frk ");
}

void		aff(t_carry *cr)
{
	char	prt;

	prt = (char)(cr->reg[cr->cycle->regs[0]]);
	if (cr->vm->a)
		ft_printf("Aff: %c\n", prt);
	if (cr->vm->debug)
		ft_printf("aff ");
}

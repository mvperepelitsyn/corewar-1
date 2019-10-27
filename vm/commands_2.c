/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:19:06 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/27 15:18:13 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		st(t_carry *cr)
{
	short			indir;

	if (cr->cycle->descript[1] == 1)
		cr->reg[cr->cycle->regs[1]] = cr->reg[cr->cycle->regs[0]];
	else
	{
		get_param_plus(cr, &indir, 1);
		indir %= IDX_MOD;
		from_var_to_memory(cr, &cr->reg[cr->cycle->regs[0]], \
			check_position(cr->position + indir), REG_SIZE);
	}
	if (cr->vm->debug)
		ft_printf("st ");
}

void		add(t_carry *cr)
{
	cr->reg[cr->cycle->regs[2]] = cr->reg[cr->cycle->regs[0]] \
		+ cr->reg[cr->cycle->regs[1]];
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("add ");
}

void		sub(t_carry *cr)
{
	cr->reg[cr->cycle->regs[2]] = cr->reg[cr->cycle->regs[0]] \
		- cr->reg[cr->cycle->regs[1]];
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("sub ");
}

void		zjmp(t_carry *cr)
{
	short			dir;

	if (!cr->carry)
		return ;
	from_memory_to_var(cr, &dir, check_position(cr->position + 1), \
g_cmd_prms[cr->cmd_code - 1].dir_size);
	dir %= IDX_MOD;
	cr->position = check_position(cr->position + dir);
	cr->cycle->shift = 1;
	if (cr->vm->debug)
		ft_printf("zjmp ");
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
	sti.position = check_position(cr->position + \
		((sti.prm2 + sti.dir2 + sti.dir3 + sti.reg3) % IDX_MOD));
	from_var_to_memory(cr, &sti.reg1, sti.position, REG_SIZE);
	if (cr->vm->debug)
		ft_printf("sti ");
}

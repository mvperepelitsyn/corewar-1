/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_ldi_lld_lldi_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:06:54 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/27 19:13:36 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ld(t_carry *cr)
{
	short			indir;
	unsigned int	posit;

	if (cr->cycle->descript[0] == 2)
		cr->reg[cr->cycle->regs[1]] = get_param(cr, 0);
	else
	{
		get_param_plus(cr, &indir, 0);
		posit = check_position(cr->position + indir % IDX_MOD);
		from_memory_to_var(cr, &cr->reg[cr->cycle->regs[1]], posit, REG_SIZE);
	}
	if (!cr->reg[cr->cycle->regs[1]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("ld ");
}

void		ldi(t_carry *cr)
{
	t_ldi		ldi;

	ft_bzero(&ldi, sizeof(ldi));
	if (cr->cycle->descript[0] == 1)
		get_param_plus(cr, &ldi.prm1, 0);
	else if (cr->cycle->descript[0] == 2)
		get_param_plus(cr, &ldi.dir1, 0);
	else
	{
		get_param_plus(cr, &ldi.indir, 0);
		from_memory_to_var(cr, &ldi.prm1, check_position(cr->position +
		ldi.indir % IDX_MOD), REG_SIZE);
	}
	if (cr->cycle->descript[1] == 1)
		get_param_plus(cr, &ldi.reg2, 1);
	else
		get_param_plus(cr, &ldi.dir2, 1);
	ldi.position = check_position(cr->position + \
		((ldi.prm1 + ldi.dir1 + ldi.dir2 + ldi.reg2) % IDX_MOD));
	from_memory_to_var(cr, &cr->reg[cr->cycle->regs[2]], ldi.position,
			REG_SIZE);
	if (cr->vm->debug)
		ft_printf("lti ");
}

void		lld(t_carry *cr)
{
	short			indir;
	unsigned int	posit;

	if (cr->cycle->descript[0] == 2)
		cr->reg[cr->cycle->regs[1]] = get_param(cr, 0);
	else
	{
		indir = get_param(cr, 0);
		posit = check_position(cr->position + indir);
		if (STUPID)
			from_memory_to_var(cr, &cr->reg[cr->cycle->regs[1]], posit, 2);
		else
			from_memory_to_var(cr, &cr->reg[cr->cycle->regs[1]], posit, \
				REG_SIZE);
	}
	if (!cr->reg[cr->cycle->regs[1]])
		cr->carry = 1;
	else
		cr->carry = 0;
	if (cr->vm->debug)
		ft_printf("lld ");
}

void		lldi(t_carry *cr)
{
	unsigned int	position;
	unsigned int	p1;
	unsigned int	p2;
	short			indir;

	if (cr->cycle->descript[0] == 3)
	{
		indir = get_param(cr, 0);
		from_memory_to_var(cr, &p1, check_position(cr->position +
		indir % IDX_MOD), REG_SIZE);
	}
	else
		p1 = get_param(cr, 0);
	p2 = get_param(cr, 1);
	position = check_position(cr->position + (p1 + p2));
	from_memory_to_var(cr, &cr->reg[cr->cycle->regs[2]], position, REG_SIZE);
	if (cr->vm->debug)
		ft_printf("lldi ");
}

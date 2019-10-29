/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:19:32 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/21 19:19:34 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** --------------------------------------------------------------------------
**						 Try to understand:
** --------------------------------------------------------------------------
*/

void				from_memory_to_var(t_carry *cr, void *var, \
int position, int size)
{
	unsigned char	*ptr;
	int				i;

	ptr = (unsigned char *)var;
	i = 0;
	if (cr->vm->l_endian)
	{
		while (i < size)
		{
			ptr[i] = cr->vm->area[check_position(position + (size - i - 1))];
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			ptr[i] = cr->vm->area[check_position(position + i)];
			i++;
		}
	}
}

static int			get_shift(t_carry *cr, int prm_nbr)
{
	int		shift;
	int		i;

	shift = (g_cmd_prms[cr->cmd_code - 1].descript) ? 2 : 1;
	i = 0;
	while (i < prm_nbr)
	{
		if (cr->cycle->descript[i] == 1)
			shift++;
		else if (cr->cycle->descript[i] == 2)
			shift += (int)g_cmd_prms[cr->cmd_code - 1].dir_size;
		else
			shift += 2;
		i++;
	}
	return (shift);
}

void				get_param_plus(t_carry *cr, void *param, int prm_nbr)
{
	unsigned int	*dst;
	int				shift;

	if (cr->cycle->descript[prm_nbr] == 1)
	{
		dst = (unsigned int*)param;
		dst[0] = cr->reg[cr->cycle->regs[prm_nbr]];
		return ;
	}
	shift = get_shift(cr, prm_nbr);
	if (cr->cycle->descript[prm_nbr] == 2)
		from_memory_to_var(cr, param, check_position(cr->position + shift), \
			g_cmd_prms[cr->cmd_code - 1].dir_size);
	else
		from_memory_to_var(cr, param, check_position(cr->position + shift), 2);
}

unsigned int		get_param(t_carry *cr, int prm_nbr)
{
	unsigned int	prm;
	int				shift;
	short			indir;

	if (cr->cycle->descript[prm_nbr] == 1)
		return (cr->reg[cr->cycle->regs[prm_nbr]]);
	shift = get_shift(cr, prm_nbr);
	if (cr->cycle->descript[prm_nbr] == 2)
		from_memory_to_var(cr, &prm, check_position(cr->position + shift), \
			g_cmd_prms[cr->cmd_code - 1].dir_size);
	else
	{
		from_memory_to_var(cr, &indir, check_position(cr->position + shift), 2);
		return (indir);
	}
	return (prm);
}

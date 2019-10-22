/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utilities_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:37:19 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/22 13:37:21 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			help_from_var_to_memory(t_carry *cr, int i,
		int position, int size)
{
	if (cr->vm->v)
	{
		if (cr->vm->l_endian)
		{
			cr->vm->back[check_position(position + (size - i - 1))] =
					cr->color - 1;
			cr->vm->light[check_position(position + (size - i - 1))] = 50;
		}
		else
		{
			cr->vm->back[check_position(position + 1)] = cr->color - 1;
			cr->vm->light[check_position(position + 1)] = 50;
		}
	}
}

void				from_var_to_memory(t_carry *cr, void *var, int position,
		int size)
{
	unsigned char	*ptr;
	int				i;

	ptr = (unsigned char *)var;
	i = 0;
	if (cr->vm->l_endian)
	{
		while (i < size)
		{
			help_from_var_to_memory(cr, i, position, size);
			cr->vm->area[check_position(position + (size - i - 1))] = ptr[i];
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			help_from_var_to_memory(cr, i, position, size);
			cr->vm->area[check_position(position + i)] = ptr[i];
			i++;
		}
	}
}

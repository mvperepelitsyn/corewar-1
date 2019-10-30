/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:26:40 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/30 16:26:40 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int		handle_type(t_placeholder *ph, va_list args, int *size, t_part **list)
{
	int		i;
	char	*str;
	t_part	*new;

	i = 0;
	while (i < (int)(sizeof(g_type) / sizeof(t_type)))
	{
		if (g_type[i].type == ph->type)
		{
			ph->padding = (ph->type == 'n') ? *size : 0;
			str = g_type[i].function(ph, args);
			if (ph->width == -1)
				return (-1);
			if (!(new = create_part(str, (size_t)ph->width)))
				exit(1);
			add_part(list, new);
			return (ph->width);
		}
		i++;
	}
	str = handle_inv_type(ph);
	if (!(new = create_part(str, (size_t)ph->width)))
		exit(1);
	add_part(list, new);
	return (ph->width);
}

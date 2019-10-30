/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:27:08 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/30 16:27:08 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

static void	update_placeholder(t_placeholder *ph)
{
	if (ph->flags & MINUS)
		ph->flags &= ~ZERO;
	ph->width = FT_MAX(ph->width, 1);
	ph->padding = ph->width - 1;
}

char		*handle_c(t_placeholder *ph, va_list args)
{
	char	*str;
	char	symbol;
	char	c;

	symbol = (char)va_arg(args, int);
	update_placeholder(ph);
	if (!(str = ft_strnew(ph->width)))
		exit(1);
	c = ((ph->flags & ZERO) ? '0' : ' ');
	if (!(ph->flags & MINUS))
		while (ph->padding > 0 && ph->padding--)
			*str++ = c;
	*str++ = symbol;
	while (ph->padding > 0 && ph->padding--)
		*str++ = c;
	return (str - ph->width);
}

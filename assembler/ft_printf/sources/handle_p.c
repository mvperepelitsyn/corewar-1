/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:26:51 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/30 16:26:52 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

static void	update_placeholder(t_placeholder *ph)
{
	ph->flags |= HASH;
}

char		*handle_p(t_placeholder *ph, va_list args)
{
	update_placeholder(ph);
	return (handle_x(ph, args));
}

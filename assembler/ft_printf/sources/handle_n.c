/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:27:01 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/30 16:27:01 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"
#include <stddef.h>

char	*handle_n(t_placeholder *ph, va_list args)
{
	int	*num;

	if ((num = va_arg(args, void *)))
	{
		if (ph->length == LENGTH_HH)
			*(signed char *)num = (signed char)ph->padding;
		else if (ph->length == LENGTH_H)
			*(short *)num = (short)ph->padding;
		else if (ph->length == LENGTH_L)
			*(long *)num = (long)ph->padding;
		else if (ph->length == LENGTH_LL)
			*(long long *)num = (long long)ph->padding;
		else if (ph->length == LENGTH_Z)
			*(ssize_t *)num = (ssize_t)ph->padding;
		else if (ph->length == LENGTH_T)
			*(ptrdiff_t *)num = (ptrdiff_t)ph->padding;
		else if (ph->length == LENGTH_J)
			*(intmax_t *)num = (intmax_t)ph->padding;
		else
			*(int *)num = (int)ph->padding;
	}
	return (ft_strdup(""));
}

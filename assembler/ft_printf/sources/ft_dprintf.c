/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:27:35 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/30 16:27:35 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_lib.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	int		size;
	va_list	args;

	va_start(args, format);
	size = ft_vdprintf(fd, format, args);
	va_end(args);
	return (size);
}

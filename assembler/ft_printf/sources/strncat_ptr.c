/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncat_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:26:15 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/30 16:26:15 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

void	strncat_ptr(char **dest, const char *src, size_t n)
{
	while (n && *src)
	{
		*(*dest)++ = *src++;
		n--;
	}
}

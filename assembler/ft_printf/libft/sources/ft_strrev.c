/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:20:42 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/30 16:20:42 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	char	*start;
	char	*end;
	char	c;

	if (s)
	{
		start = s;
		end = s + (ft_strlen(s) - 1);
		while (start < end)
		{
			c = *start;
			*start++ = *end;
			*end-- = c;
		}
	}
	return (s);
}

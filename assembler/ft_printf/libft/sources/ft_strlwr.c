/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlwr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:21:43 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/30 16:21:43 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlwr(char *s)
{
	size_t i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			s[i] = (char)ft_tolower(s[i]);
			i++;
		}
	}
	return (s);
}

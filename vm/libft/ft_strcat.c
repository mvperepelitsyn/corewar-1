/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 19:49:23 by uhand             #+#    #+#             */
/*   Updated: 2019/08/01 13:25:40 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	len;

	len = ft_strlen(s1);
	while (s2[0] != '\0')
	{
		s1[len] = (char)s2[0];
		len++;
		s2++;
	}
	s1[len] = '\0';
	return (s1);
}

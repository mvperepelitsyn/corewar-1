/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compile_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:57:30 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/16 17:57:32 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

char	*ft_str_realloc(char *str, int i)
{
	char	*temp;

	if (i == 0)
		return (str);
	temp = (char *)realloc(str, ((i / 100000) * 100000 + 100000));
	free(str);
	return (temp);
}

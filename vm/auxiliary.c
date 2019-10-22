/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:16:33 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/22 14:08:57 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	short_ind(unsigned char *dst, unsigned const char *src)
{
	if (ft_islitendian())
	{
		dst[1] = src[0];
		dst[0] = src[1];
	}
	else
	{
		dst[0] = src[0];
		dst[1] = src[1];
	}
}

int		display_usage(void)
{
	ft_printf("usage:\n\there should be an explanation\n");
	return (0);
}

int		ft_err_plus(char *str, long int num, char *hlp_str, int toggle)
{
	if (toggle == 0)
		ft_printf(str, num);
	else if (toggle == 1)
		ft_printf(str, hlp_str);
	else
		ft_putstr("ERROR!\n");
	exit(69);
}

int		ft_error(char *str)
{
	if (!str)
		ft_putstr("ERROR\n");
	else
		ft_printf("%s\n", str);
	exit(69);
}

int		check_position(int position)
{
	while (position < 0 || position >= MEM_SIZE)
	{
		if (position < 0)
			position += MEM_SIZE;
		else if (position >= MEM_SIZE)
			position -= MEM_SIZE;
	}
	return (position);
}

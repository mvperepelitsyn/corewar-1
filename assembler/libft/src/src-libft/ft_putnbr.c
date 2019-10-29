/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 21:43:03 by ggerhold          #+#    #+#             */
/*   Updated: 2019/05/02 21:43:03 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr(int n)
{
	int	t;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		return (ft_putnbr(-n) + 1);
	}
	else if (n > 9)
	{
		t = ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
		return (t + 1);
	}
	ft_putchar(n + 48);
	return (1);
}

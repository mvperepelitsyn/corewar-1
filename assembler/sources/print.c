/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:09:55 by thansen           #+#    #+#             */
/*   Updated: 2019/10/30 16:09:59 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_asm.h"
#include "ft_printf.h"

void	print_help(void)
{
	ft_printf("Usage: ./asm (champion.s|champion.cor)\n");
	ft_printf("    champion.s   — from assemble to bytecode\n");
	ft_printf("    champion.cor — from bytecode to assemble\n");
}

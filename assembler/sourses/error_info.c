/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:51 by thansen           #+#    #+#             */
/*   Updated: 2019/10/30 16:07:53 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_asm.h"
#include "ft_printf.h"

void	name_error(void)
{
	ft_dprintf(2, "Champion name too long (Max length %u)\n", PROG_NAME_LENGTH);
	exit(1);
}

void	comment_error(void)
{
	ft_dprintf(2, "Champion comment too long (Max length %u)\n",
																COMMENT_LENGTH);
	exit(1);
}

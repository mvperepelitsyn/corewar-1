/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:50:27 by thansen           #+#    #+#             */
/*   Updated: 2019/10/29 22:50:28 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <errno.h>

int		main(int argc, char **argv)
{
	errno = 0;
	if (argc == 2 && is_filename(*(argv + 1), ".s"))
		assemble(*(argv + 1));
	else
		print_help();
	return (0);
}

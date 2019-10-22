/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:35:41 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/22 16:35:50 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	declare_champs(t_process *p)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < MAX_PLAYERS)
	{
		if (p[i].cmp_nbr)
			ft_printf("* Player %hhu, weighing %llu bytes, \"%s\" (\"%s\") !\n",
					p[i].cmp_nbr, p[i].code_size, p[i].cmp_name, p[i].cmp_cmnt);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_vm	vm;

	if (argc < 2)
		return (display_usage());
	ft_bzero((void*)&vm, sizeof(vm));
	parsing(argc, argv, &vm);
	declare_champs(&vm.processes[0]);
	vm_init(&vm);
	game(&vm);
	exit(0);
}

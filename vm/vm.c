/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:35:41 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/21 20:35:43 by dfrost-a         ###   ########.fr       */
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

static void	clean_champs(t_vm *vm)
{
	int i;

	i = 0;
	while (i < vm->champs_count)
	{
		if (vm->processes[i].cmp_name)
		{
			ft_strdel(&vm->processes[i].cmp_name);
			ft_strdel(&vm->processes[i].cmp_cmnt);
			ft_strdel((char **)&vm->processes[i].code);
		}
		i++;
	}
	ft_strdel((char **)&vm->area);
	if (vm->v)
		ft_strdel((char **)&vm->back);
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
//	clean_champs(&vm);
	exit(0);
}

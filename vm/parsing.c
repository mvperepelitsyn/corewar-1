/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:28:38 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/21 15:28:50 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	parse_dump_flag(t_vm *vm, char **argv, int l)
{
	if (!ft_isnumber(argv[l]))
		ft_err_plus("Error! After flag -dump supposed to be a number, this is "
"\"%s\" not a number!\n", 0, argv[l], 1);
	vm->dump_flag = 1;
	vm->dump = ft_atoi(argv[l]);
	if (vm->dump != (long long int)ft_latoi(argv[l]))
		ft_err_plus("Error! The number %d after flag -dump is invalid!\n",
vm->dump, NULL, 0);
}

static void	check_num_for_n_flag(char **argv, int *l)
{
	*l = *l + 1;
	if (!ft_isnumber(argv[*l]))
		ft_err_plus("Error! After flag -n supposed to be a number, this is "
"\"%s\" not a number!\n", 0, argv[*l], 1);
}

static void	parse_champ(int argc, char **argv, t_vm *vm, int l)
{
	long int	num;

	while (l < argc)
	{
		if (ft_strequ(argv[l], "-n"))
		{
			check_num_for_n_flag(argv, &l);
			check_num(vm->processes, num = ft_atoi(argv[l]), argv[l + 1]);
			l++;
			check_file_and_fill(argv[l], vm->processes, num);
		}
		else if (ft_strequ(argv[l], "-dump"))
		{
			l++;
			parse_dump_flag(vm, argv, l);
		}
		else if (ft_strequ(argv[l], "-v"))
			vm->v = 1;
		else if (ft_strequ(argv[l], "-a"))
			vm->a = 1;
		else
			check_file_and_fill(argv[l], vm->processes, 0);
		l++;
	}
	how_many_champs(vm);
}

static void	ft_set_champs_to_null(t_process *champs)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		champs[i].cmp_nbr = 0;
		champs[i].cmp_name = NULL;
		champs[i].cmp_cmnt = NULL;
		champs[i].code_size = 0;
		champs[i].code = NULL;
		i++;
	}
}

void		parsing(int argc, char **argv, t_vm *vm)
{
	int i;

	i = 0;
	if (argc > 16)
		ft_error("Error! Too many arguments");
	else
	{
		ft_set_champs_to_null(vm->processes);
		parse_champ(argc, argv, vm, 1);
		while (i < MAX_PLAYERS)
		{
			if (vm->processes[i].cmp_nbr > 0 &&
			vm->processes[i].cmp_nbr > vm->champs_count)
				ft_error("Error! The number after flag -n has to be less than"
" the total number of champions that fighting in the battle!");
			i++;
		}
	}
}

#include "vm.h"



static void	check_num(t_process *champs, int num)
{
	int i;

	i = 0;
	if (num < 1 || num > MAX_PLAYERS)
		ft_error("Wrong number of champion file!\n");
	while (i < MAX_PLAYERS)
	{
		if (champs[i].cmp_nbr == num)
			ft_error("Wrong number of champion file!\n");
		i++;
	}
}

static void check_file_name(char *file_name, t_process *chmp, int num)
{
	int		i;
	char 	*tmp;

	tmp = NULL;
	i = ft_strlen(file_name);
	tmp = ft_strsub(file_name, i - 4, 4);
	if (!ft_strequ(tmp, ".cor"))
		ft_error("Wrong type of the champion file!\n");
	ft_strdel(&tmp);
	i = 0;
	if (num != 0)
		chmp->cmp_nbr = num;
	else
	{
		while (i < MAX_PLAYERS)
		{
			if (chmp[i].cmp_nbr == 0)
			i++;
		}
	}

	fill_the_champ(chmp, file_name);
}

static void	parse_champ(int argc, char **argv, t_vm *vm)
{
	int			l;
	long int 	num;

	l = 1;
	while (l <= argc)
	{
		if (ft_strequ(argv[l], "-n"))
		{
			l++;
			check_num(vm->processes, num = ft_atoi(argv[l]));
			l++;
			check_file_name(argv[l], vm->processes, num);
		}
		else if (ft_strequ(argv[l], "-dump"))
		{
			l++;
			if ((num = ft_atoi(argv[l])) < 0 || num != (long long int)ft_latoi
			(argv[l]))
				ft_error("Invalid number after after flag -dump.\n");
		}
		else
			check_file_name(argv[l], vm->processes, 0);
		l++;
	}
}

void		parsing(int argc, char **argv, t_vm	*vm)
{
	if (argc > 15)
		ft_error("Too many arguments");
	else
		parse_champ(argc, argv, vm);
}

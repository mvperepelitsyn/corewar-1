# include "vm.h"

static void	check_num(t_process *champs, int num)
{
	t_process	*tmp;

	if (num < 1 || num > MAX_PLAYERS)
		ft_error("Wrong number of champion!\n");
	if (champs == NULL)
		return ;
	tmp = champs;
	while (tmp)
	{
		if (tmp->cmp_nbr == num)
			ft_error("Wrong number of champion!\n");
		tmp = tmp->next;
	}
}

static void	parse_champ(int argc, char **argv, t_vm *vm)
{
	int			l;
	int 		num;
	t_process	*chmp;

	l = 1;
	chmp = vm->processes;
	while (l <= argc)
	{
		if (ft_strequ(argv[l], "-n"))
		{
			if (!(chmp = (t_process *)ft_memalloc(sizeof(t_process))))
				ft_error("Malloc couldn't allocate the memory\n");
			l++;
			chmp->cmp_nbr = ft_atoi(argv[l]);
			l++;

		}
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

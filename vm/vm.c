# include "vm.h"

static void	declare_champs(t_process *p)
{
	int		i;

	i = 0;
	while(p[i].cmp_nbr)
	{
		ft_printf("* Player %hhu, weighing %llu bytes, \"%s\" (\"%s\") !\n", \
			p[i].cmp_nbr, p[i].code_size, p[i].cmp_name, p[i].cmp_cmnt);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_vm	vm;

//	ft_printf("\033[4;31m This text is red with yellow background \033[0m This text has default color\n");
//
//	exit (69);
	if (argc < 2)
		return(display_usage());
	ft_bzero((void*)&vm, sizeof(vm));
	parsing(argc, argv, &vm);
	declare_champs(&vm.processes[0]);
	vm_init(&vm);
	game(&vm);
	return (0);
}

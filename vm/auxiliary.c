# include "vm.h"

int		display_usage()
{
	ft_printf("usage:\n\there should be an explanation\n");
	return (0);
}

void	ft_error(char *str)
{
	if (!str)
		ft_putstr("ERROR\n");
	else
		ft_printf("%s\n", str);
	exit(69);
}

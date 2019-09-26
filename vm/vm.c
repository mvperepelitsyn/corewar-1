# include "vm.h"

int		main(int argc, char **argv)
{
	t_vm	vm;

	if (argc < 2)
		return(display_usage());
	parsing(argc, argv, &vm);
	vm_init(&vm);
	return (0);
}

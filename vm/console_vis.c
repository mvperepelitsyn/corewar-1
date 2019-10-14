# include "vm.h"

void		print_game_area(t_vm *vm)
{
	unsigned int	byte;

	byte = 0;
	while (byte < MEM_SIZE)
	{
		if (byte)
			ft_printf("%#06x : ", byte);
		else
			ft_printf("0x0000 : ");
		while (byte % 32 < 31)
		{
			ft_printf("%02x ", (unsigned int)vm->area[byte]);
			byte++;
		}
		ft_printf("%02x\n", (unsigned int)vm->area[byte]);
		byte++;
	}
}

static int	check_car_position(t_vm *vm, int pos, unsigned char *color)
{
	t_carry			*cr;

	cr = vm->carriages;
	while (cr)
	{
		if (pos == cr->position)
		{
			*color = (cr->color == 3) ? 45 : cr->color + 40;
			return (1);
		}
		cr = cr->next;
	}
	return (0);
}

static void	print_byte(t_vm *vm, int byte, char ending)
{
	unsigned char	cr_clr;
	unsigned char	color;
	unsigned char	cycles;

	if (vm->back[byte] != 255)
		color = (vm->back[byte] == 2) ? 35 : vm->back[byte] + 31;
	else if (vm->back[byte] == 255)
		color = 37;
	else
	{
		cycles = (vm->back[byte] >> 2) - 1;
		cr_clr = vm->back[byte] << 6;
		cr_clr >>= 2;
	}
	if (!check_car_position(vm, byte, &cr_clr))
		ft_printf("\033[%hhum%02x\033[0m%c", color, \
			(unsigned int)vm->area[byte], ending);
	else
		ft_printf("\033[30;%hhum%02x\033[0m%c", cr_clr, \
			(unsigned int)vm->area[byte], ending);
}

void	game_area_frame(t_vm *vm)
{
	int				byte;

	byte = -1;
	// ft_printf("\e[1;1H\e[2J");
	ft_printf("\nCycles from start: %u\n", vm->cycles_from_start);
	while (++byte < MEM_SIZE)
	{
		if (byte)
			ft_printf("%#06x : ", byte);
		else
			ft_printf("0x0000 : ");
		while (byte % 64 < 63)
		{
			print_byte(vm, byte, ' ');
			byte++;
		}
		print_byte(vm, byte, '\n');
	}
	usleep(20000);
	ft_printf("\e[1;1H\e[2J");
}

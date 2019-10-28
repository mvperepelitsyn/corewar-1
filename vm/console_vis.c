/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_vis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:58:24 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/28 17:46:25 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

static void	print_byte_norma(t_vm *vm, int byte, char ending,
		unsigned char color)
{
	if (!vm->light[byte])
	{
		if (color == 37)
			ft_printf("\033[2;%hhum%02x\033[0m%c", color, \
				(unsigned int)vm->area[byte], ending);
		else
			ft_printf("\033[%hhum%02x\033[0m%c", color, \
				(unsigned int)vm->area[byte], ending);
	}
	else
	{
		ft_printf("\033[1;%hhum%02x\033[0m%c", color, \
			(unsigned int)vm->area[byte], ending);
		vm->light[byte]--;
	}
}

static void	print_byte(t_vm *vm, int byte, char ending)
{
	unsigned char	cr_clr;
	unsigned char	color;

	if (vm->back[byte] != 255 && vm->back[byte] < 4)
		color = (vm->back[byte] == 2) ? 35 : vm->back[byte] + 31;
	else if (vm->back[byte] == 255)
		color = 37;
	else
	{
		cr_clr = vm->back[byte] << 6;
		cr_clr >>= 6;
		cr_clr = (cr_clr == 2) ? 45 : cr_clr + 41;
		ft_printf("\033[0;%hhum%02x\033[0m%c", cr_clr, \
			(unsigned int)vm->area[byte], ending);
		vm->back[byte] -= 4;
		return ;
	}
	if (!check_car_position(vm, byte, &cr_clr))
		print_byte_norma(vm, byte, ending, color);
	else
		ft_printf("\033[30;%hhum%02x\033[0m%c", cr_clr, \
			(unsigned int)vm->area[byte], ending);
}

static void	print_report(t_vm *vm)
{
	t_carry		*cr;

	cr = vm->carriages;
	ft_printf("\nCycles from start: %u\t\tCycles to die: %d\tTotal lives: %u", \
		vm->cycles_from_start, vm->cycles_to_die, vm->live_counter);
	ft_printf("\t\tLast alive champion: \"%s\"(%d / %u)\n\n", \
		vm->processes[(vm->last_alive * -1) - 1].cmp_name, \
		vm->last_alive, vm->last_alive_cycle);
	while (cr)
	{
		if (cr->last_champ)
		{
			ft_printf("%s \"%s\" (%d) said \"Alive!\" %d cycles ago (%u).\t", \
				"Champion", vm->processes[(cr->last_champ * -1) - 1].cmp_name, \
				cr->last_champ, cr->last_live, cr->last_alive_cycle);
		}
		if (cr->cmd_code >= 1 && cr->cmd_code <= 16 \
				&& !(vm->dump_flag && !vm->dump))
			ft_printf("\tNext command: \"%s\" in %u cycles\n", \
				g_cmd_prms[cr->cmd_code - 1].name, cr->cycles_before);
		else if (!(vm->dump_flag && !vm->dump))
			ft_printf("\tWrong command code: %hhu\n", cr->cmd_code);
		cr = cr->next;
	}
	ft_printf("\n");
}

void		game_area_frame(t_vm *vm)
{
	int				byte;

	byte = -1;
	ft_printf("\e[1;1H\e[2J");
	// system("clear");
	print_report(vm);
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
	usleep(SLEEP);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:07:42 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/30 19:07:44 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	check_num_for_n_flag(char **argv, int argc, int *l)
{
	*l = *l + 1;
	if (*l >= argc)
		ft_error("Error! There is no number, no argument after flag -n! Watch o"
"ut! Next time it'll be a ticket for you!");
	if (!ft_isnumber(argv[*l]))
		ft_err_plus("Error! After flag -n supposed to be a number, this is "
					"\"%s\", it's not a number!\n", 0, argv[*l], 1);
}

void		parse_flag_n(int argc, char **argv, t_vm *vm, int *l)
{
	int num;

	num = 0;
	check_num_for_n_flag(argv, argc, l);
	check_num(vm->processes, num = ft_atoi(argv[*l]), argv[*l + 1]);
	*l = *l + 1;
	check_file_and_fill(argv[*l], vm->processes, num);
}

static void	set_the_verbose(t_vm *vm)
{
	if (vm->verbose.v_num & 16)
		vm->verbose.v_16 = 1;
	if (vm->verbose.v_num & 8)
		vm->verbose.v_8 = 1;
	if (vm->verbose.v_num & 4)
		vm->verbose.v_4 = 1;
	if (vm->verbose.v_num & 2)
		vm->verbose.v_2 = 1;
	if (vm->verbose.v_num & 1)
		vm->verbose.v_1 = 1;
}

void		parse_verbose_flag(char **argv, int argc, int *l, t_vm *vm)
{
	int num;

	*l = *l + 1;
	ft_bzero(&vm->verbose, sizeof(t_verbose));
	if (*l >= argc)
		ft_error("Error! There is no number, no argument after flag -v! Watch "
"out! Next time it'll be a ticket for you!");
	if (!ft_isnumber(argv[*l]))
		ft_err_plus("Error! After flag -v supposed to be a number, this is "
					"\"%s\", it's not a number!\n", 0, argv[*l], 1);
	num = ft_atoi(argv[*l]);
	if (num < 0 || num > 31 || num != (long long int)ft_latoi(argv[*l]))
		ft_err_plus("Error! This number %s after flag -v is invalid!\n", 0,
					argv[*l], 1);
	if (num > 0 && num <= 31)
	{
		vm->verbose.v = 1;
		vm->verbose.v_num = num;
		set_the_verbose(vm);
	}
}

void		print_lldi(t_carry *cr, t_ldi *ldi)
{
	if (cr->vm->verbose.v && cr->vm->verbose.v_4)
	{
		ft_printf("P%*d | lldi %d %d r%d\n       | -> load from %d + %d = %d (w"
"ith pc %d)\n", ((ft_hw_mn_orders(cr->car_nbr) < 5) ? 5 : ft_hw_mn_orders(cr->
car_nbr) + 1), cr->car_nbr, ldi->prm1 + ldi->dir1, ldi->dir2 + ldi->reg2, cr->
cycle->regs[2] + 1, ldi->prm1 + ldi->dir1, ldi->dir2 + ldi->reg2,
ldi->prm1 + ldi->dir1 + ldi->dir2 + ldi->reg2, ldi->position);
	}
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
}

# include "vm.h"

/*
** Calculate command bytes length:
*/

void		calc_shift(t_carry *cr, t_cycle *cycle)
{
	int		i;

	i = 0;
	if (g_cmd_prms[cr->cmd_code - 1].descript)
		cr->jump_len++;
	else
	{
		cr->jump_len += (int)g_cmd_prms[cr->cmd_code - 1].dir_size;
		return ;
	}
	while (i < g_cmd_prms[cr->cmd_code - 1].prms_count)
	{
		if (cycle->descript[i] == 1)
			cr->jump_len++;
		else if (cycle->descript[i] == 2)
			cr->jump_len += (int)g_cmd_prms[cr->cmd_code - 1].dir_size;
		else
			cr->jump_len += 2;
		i++;
	}
}

/*
** Check reg number valid range:
*/

static int	check_reg(t_vm *vm, t_carry *cr, t_cycle *cycle)
{
	int		i;
	int		shift;

	i = 0;
	shift = 2;
	while (i < g_cmd_prms[cr->cmd_code - 1].prms_count)
	{
		if (cycle->descript[i] == 1 && !(vm->area[cr->position + shift] >= 1 \
				&& vm->area[cr->position + shift] <= 16))
			return (0);
		if (cycle->descript[i] == 1)
			shift++;
		else if (cycle->descript[i] == 2)
			shift += (int)g_cmd_prms[cr->cmd_code - 1].dir_size;
		else
			shift += 2;
		i++;
	}
	return (1);
}

/*
** Check valid params types:
*/

static int	check_params_type(t_carry *cr, t_cycle *cycle)
{
	int		i;

	i = 0;
	while (i < g_cmd_prms[cr->cmd_code - 1].prms_count)
	{
		if ((cycle->descript[i] == 1 && \
				!(g_cmd_prms[cr->cmd_code - 1].prm_types[i] & 1)) || \
				(cycle->descript[i] == 2 && \
				!(g_cmd_prms[cr->cmd_code - 1].prm_types[i] & 2)) || \
				(cycle->descript[i] == 3 && \
				!(g_cmd_prms[cr->cmd_code - 1].prm_types[i] & 4)))
			return (0);
		i++;
	}
	return (1);
}

/*
** Check valid params count:
*/

static int	check_params(t_vm *vm, t_carry *cr, t_cycle *cycle)
{
	unsigned char	buf;

	buf = vm->area[cr->position + 1];
	if ((buf <<= 6) > 0)
		return (0);
	buf = vm->area[cr->position + 1];
	buf <<= 4;
	buf >>= 6;
	cycle->descript[2] = buf;
	buf = vm->area[cr->position + 1];
	buf <<= 2;
	buf >>= 6;
	cycle->descript[1] = buf;
	buf = vm->area[cr->position + 1];
	buf >>= 6;
	cycle->descript[0] = buf;
	if ((g_cmd_prms[cr->cmd_code - 1].prms_count < 3 && cycle->descript[2]) || \
			(g_cmd_prms[cr->cmd_code - 1].prms_count < 2 && cycle->descript[1]))
		return (0);
	return (check_params_type(cr, cycle));
}

int			check_operation(t_vm *vm, t_carry *cr, t_cycle *cycle)
{
	if (!(cr->cmd_code >= 1 && cr->cmd_code <= 16))
		return (0);
	if (g_cmd_prms[cr->cmd_code - 1].descript)
	{
		if (!check_params(vm, cr, cycle) || !check_reg(vm, cr, cycle))
		{
			calc_shift(cr, cycle);
			return (0);
		}
	}
	calc_shift(cr, cycle);
	return(1);
}

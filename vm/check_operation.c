# include "vm.h"

void		calc_shift(t_carry *cr)
{
	//
}

static int	check_reg(t_carry *cr, t_cycle *cycle)
{
	//
	return (1);
}

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
	if ((g_cmd_prms.prms_count < 3 && cycle->descript[2]) || \
			(g_cmd_prms.prms_count < 2 && cycle->descript[1]))
		return (0);
	// if ((g_cmd_prms.prm_types[0] & ) )
	// 	;
	return (1);
}

int			check_operation(t_vm *vm, t_carry *cr, t_cycle *cycle)
{
	if (!(cr->cmd_code >= 1 && cr->cmd_code <= 16))
		return (0);
	if (g_cmd_prms[cr->cmd_code - 1].descript)
	{
		if (!check_params(vm, cr, cycle) || !check_reg(cr, cycle))
		{
			calc_shift(cr);
			return (0);
		}
	}
	calc_shift(cr);
	return(1);
}

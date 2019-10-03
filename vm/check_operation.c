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

static int	check_params(t_carry *cr, t_cycle *cycle)
{
	unsigned char	buf;

	buf = g_cmd_prms[cr->cmd_code - 1].descript;
	return (1);
}

int			check_operation(t_vm *vm, t_carry *cr, t_cycle *cycle)
{
	if (!(cr->cmd_code >= 1 && cr->cmd_code <= 16))
		return (0);
	if (g_cmd_prms[cr->cmd_code - 1].descript)
	{
		if (!check_params(cr, cycle) || !check_reg(cr, cycle))
		{
			calc_shift(cr);
			return (0);
		}
	}
	calc_shift(cr);
	return(1);
}

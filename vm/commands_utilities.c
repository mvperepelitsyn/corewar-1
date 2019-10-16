//
// Created by Dwarven centurion Frost atronach on 2019-10-09.
//

#include "vm.h"

static unsigned int	help_get_param(t_carry *cr, int src_i, int i)
{
	unsigned char	*dest;
	unsigned int	prm;

	dest = (unsigned char *)&prm;
	while (i < g_cmd_prms[cr->cmd_code - 1].dir_size)
	{
		dest[i] = cr->vm->area[check_position(src_i + i)];
		i++;
	}
	if (ft_islitendian())
		prm = ft_reverseint(prm);
	return (prm);
}

/*
	AM I RIGHT WHEN I AM TRYING TO REACH THE NEEDED 3D ARGUMENT???
*/

unsigned int		get_param3(t_carry *cr)
{
	unsigned int	prm;
	int 			src_i;

	prm = 0;
	if (cr->cycle->descript[2] == 1)
		prm = cr->reg[cr->cycle->descript[2]];
	else if (cr->cycle->descript[2] == 2)
	{
//		src_i = check_position(cr->position + 2 +
//							   (2 * g_cmd_prms[cr->cmd_code - 1].dir_size));
		src_i = check_position(cr->position + 2 + 1 + g_cmd_prms[cr->cmd_code - 1].dir_size);
		prm = help_get_param(cr, src_i, 0);
	}
	return (prm);
}

// unsigned int		get_param(t_carry *cr, short toggle)
// {
// 	unsigned int	prm;
// 	unsigned char	*dest;
// 	short			indir;
// 	int 			src_i;
//
// 	prm = 0;
// 	if (cr->cycle->descript[toggle] == 1)
// 		prm = cr->reg[cr->cycle->descript[toggle]];
// 	else if (cr->cycle->descript[toggle] == 2)
// 	{
// //		src_i = (toggle == 0) ? check_position(cr->position + 2) :
// //				check_position(cr->position + 2 + g_cmd_prms[cr->cmd_code -
// //				1].dir_size);
// 		src_i = cr->position + 2 + 1;
// 		prm = help_get_param(cr, src_i, 0);
// 	}
// 	else if (cr->cycle->descript[toggle] == 3)
// 	{
// 		src_i = (toggle == 0) ? check_position(cr->position + 2) :
// 				check_position(cr->position + 4);
// 		dest = (unsigned char *)&indir;
// 		if (cr->vm->l_endian)
// 		{
// 			dest[1] = cr->vm->area[src_i];
// 			dest[0] = cr->vm->area[check_position(src_i + 1)];
// 		}
// 		else
// 		{
// 			dest[0] = cr->vm->area[src_i];
// 			dest[1] = cr->vm->area[src_i + 1];
// 		}
// 		indir = indir_position(indir, cr);
// 		prm = help_get_param(cr, indir, 0);
// 	}
// 	return (prm);
// }

/*
** --------------------------------------------------------------------------
**						 Try to understanding:
** --------------------------------------------------------------------------
*/

void			from_var_to_memory(t_carry *cr, void *var, \
	int position, int	size)
{
	unsigned char	*ptr;
	int				i;

	ptr = (unsigned char *)var;
	i = 0;
	if (cr->vm->l_endian)
	{
		while (i < size)
		{
			if (cr->vm->v)
				cr->vm->back[check_position(position + (size - i - 1))] =
						cr->color - 1;
			cr->vm->area[check_position(position + (size - i - 1))] = ptr[i];
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			if (cr->vm->v)
				cr->vm->back[check_position(position + 1)] = cr->color - 1;
			cr->vm->area[check_position(position + i)] = ptr[i];
			i++;
		}
	}
}


void			from_memory_to_var(t_carry *cr, void *var, \
	int position, int	size)
{
	unsigned char	*ptr;
	int				i;

	ptr = (unsigned char *)var;
	i = 0;
	if (cr->vm->l_endian)
	{
		while (i < size)
		{
			ptr[i] = cr->vm->area[check_position(position + (size - i - 1))];
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			ptr[i] = cr->vm->area[check_position(position + i)];
			i++;
		}
	}
}

static int		get_shift(t_carry *cr, int prm_nbr)
{
	int		shift;
	int		i;

	shift = (g_cmd_prms[cr->cmd_code - 1].descript) ? 2 : 1;
	i = 0;
	while (i < prm_nbr)
	{
		if (cr->cycle->descript[i] == 1)
			shift++;
		else if (cr->cycle->descript[i] == 2)
			shift += (int)g_cmd_prms[cr->cmd_code - 1].dir_size;
		else
			shift += 2;
		i++;
	}
	return (shift);
}

unsigned int	get_param(t_carry *cr, int prm_nbr)
{
	unsigned int	prm;
	int				shift;
	short			indir;

	if (cr->cycle->descript[prm_nbr] == 1)
		return (cr->reg[cr->cycle->regs[prm_nbr]]);
	shift = get_shift(cr, prm_nbr);
	if (cr->cycle->descript[prm_nbr] == 2)
		from_memory_to_var(cr, &prm, check_position(cr->position + shift), \
			g_cmd_prms[cr->cmd_code - 1].dir_size);
	else
	{
		from_memory_to_var(cr, &indir, check_position(cr->position + shift), 2);
		// from_memory_to_var(cr, &prm, check_position(cr->position + indir), 4);
		return (indir);
	}
	return (prm);
}

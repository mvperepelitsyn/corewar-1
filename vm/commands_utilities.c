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
		src_i = check_position(cr->position + 2 +
							   (2 * g_cmd_prms[cr->cmd_code - 1].dir_size));
		prm = help_get_param(cr, src_i, 0);
	}
	return (prm);
}

unsigned int		get_param(t_carry *cr, short toggle)
{
	unsigned int	prm;
	unsigned char	*dest;
	short			indir;
	int 			src_i;

	prm = 0;
	if (cr->cycle->descript[toggle] == 1)
		prm = cr->reg[cr->cycle->descript[toggle]];
	else if (cr->cycle->descript[toggle] == 2)
	{
		src_i = (toggle == 0) ? check_position(cr->position + 2) :
				check_position(cr->position + 2 + g_cmd_prms[cr->cmd_code -
				1].dir_size);
		prm = help_get_param(cr, src_i, 0);
	}
	else if (cr->cycle->descript[toggle] == 3)
	{
		src_i = (toggle == 0) ? check_position(cr->position + 2) :
				check_position(cr->position + 4);
		dest = (unsigned char *)&indir;
		if (cr->vm->l_endian)
		{
			dest[1] = cr->vm->area[src_i];
			dest[0] = cr->vm->area[check_position((src_i) + 1)];
		}
		else
		{
			dest[0] = cr->vm->area[src_i];
			dest[1] = cr->vm->area[src_i + 1];
		}
		indir = indir_position(indir, cr);
		prm = help_get_param(cr, indir, 0);
	}
	return (prm);
}

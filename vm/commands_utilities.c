//
// Created by Dwarven centurion Frost atronach on 2019-10-09.
//

#include "vm.h"

static unsigned int	help_get_param(t_carry *cr, unsigned const char *src, int i)
{
	unsigned char	*dest;
	unsigned int	prm;

	dest = (unsigned char *)&prm;
	while (i < g_cmd_prms[cr->cmd_code - 1].dir_size)
	{
		dest[i] = src[i];
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
	unsigned char	*src;

	prm = 0;
	if (cr->cycle->descript[2] == 1)
		prm = cr->reg[cr->cycle->descript[2]];
	else if (cr->cycle->descript[2] == 2)
	{
		src = &cr->vm->area[cr->position + 2 +
					  (2 * g_cmd_prms[cr->cmd_code - 1].dir_size)];
		prm = help_get_param(cr, src, 0);
	}
	return (prm);
}

unsigned int		get_param(t_carry *cr, short toggle)
{
	unsigned int	prm;
	unsigned char	*dest;
	short			indir;
	unsigned char	*src;

	prm = 0;
	if (cr->cycle->descript[toggle] == 1)
		prm = cr->reg[cr->cycle->descript[toggle]];
	else if (cr->cycle->descript[toggle] == 2)
	{
		src = (toggle == 0) ? &cr->vm->area[cr->position + 2] : &cr->vm->area[cr
					->position + 2 + g_cmd_prms[cr->cmd_code - 1].dir_size];
		prm = help_get_param(cr, src, 0);
	}
	else if (cr->cycle->descript[toggle] == 3)
	{
		src = (toggle == 0) ? &cr->vm->area[cr->position + 2] :
			&cr->vm->area[cr->position + 4];
		dest = (unsigned char *)&indir;
		short_ind(dest, src);
		indir = indir_position(indir, cr);
		src = &cr->vm->area[indir];
		prm = help_get_param(cr, src, 0);
	}
	return (prm);
}

//
// Created by Dwarven centurion Frost atronach on 2019-10-09.
//

#include "vm.h"

static short	help_andorxor(t_carry *cr, short toggle,
		unsigned const char *src, int i)
{
	unsigned char	*dest;
	short			dir;

	dest = (unsigned char *)&dir;
	if (src == NULL)
	{
		while (i < g_cmd_prms[cr->cmd_code - 1].dir_size)
		{
			dest[i] = (toggle == 0) ? cr->vm->area[cr->position + 2 + i] :
					cr->vm->area[cr->position + 6 + i];
			i++;
		}
	}
	else
	{
		while (i < g_cmd_prms[cr->cmd_code - 1].dir_size)
		{
			dest[i] = src[i];
			i++;
		}
	}
	if (ft_islitendian())
		dir = ft_reverseint(dir);
	return (dir);
}

static short	andorxor(t_carry *cr, short toggle)
{
	unsigned int	dir;
	unsigned char	*dest;
	short			in;
	unsigned char	*src;

	dir = 0;
	if (cr->cycle->descript[toggle] == 1)
		dir = cr->reg[cr->cycle->descript[toggle]];
	else if (cr->cycle->descript[toggle] == 2)
		dir = help_andorxor(cr, toggle, NULL, 0);
	else if (cr->cycle->descript[toggle] == 3)
	{
		src = (toggle == 0) ? &cr->vm->area[cr->position + 2] :
			&cr->vm->area[cr->position + 4];
		dest = (unsigned char *)&in;
		short_ind(dest, src);
		in = indir_position(in, cr);
		src = &cr->vm->area[in];
		dir = help_andorxor(cr, toggle, src, 0);
	}
	return (dir);
}

/*
** It has to be checked carefully!
*/

void			and(t_carry *cr)
{
	unsigned int	dir1;
	unsigned int	dir2;

	dir1 = andorxor(cr, 0);
	dir2 = andorxor(cr, 1);
	cr->reg[cr->cycle->descript[2]] = dir1 & dir2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	ft_printf("and ");
}

void			or(t_carry *cr)
{
	unsigned int	dir1;
	unsigned int	dir2;

	dir1 = andorxor(cr, 0);
	dir2 = andorxor(cr, 1);
	cr->reg[cr->cycle->descript[2]] = dir1 | dir2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	ft_printf("or ");
}

void			xor(t_carry *cr)
{
	unsigned int	dir1;
	unsigned int	dir2;

	dir1 = andorxor(cr, 0);
	dir2 = andorxor(cr, 1);
	cr->reg[cr->cycle->descript[2]] = dir1 ^ dir2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	ft_printf("xor ");
}

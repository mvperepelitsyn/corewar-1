//
// Created by Dwarven centurion Frost atronach on 2019-10-09.
//

#include "vm.h"

static short	help_andorxor(t_carry *cr, unsigned const char *src, int i)
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

unsigned int	get_param(t_carry *cr, short toggle)
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
		prm = help_andorxor(cr, src, 0);
	}
	else if (cr->cycle->descript[toggle] == 3)
	{
		src = (toggle == 0) ? &cr->vm->area[cr->position + 2] :
			&cr->vm->area[cr->position + 4];
		dest = (unsigned char *)&indir;
		short_ind(dest, src);
		indir = indir_position(indir, cr);
		src = &cr->vm->area[indir];
		prm = help_andorxor(cr, src, 0);
	}
	return (prm);
}

/*
** It has to be checked carefully!
*/

void			and(t_carry *cr)
{
	unsigned int	prm1;
	unsigned int	prm2;

	prm1 = get_param(cr, 0);
	prm2 = get_param(cr, 1);
	cr->reg[cr->cycle->descript[2]] = prm1 & prm2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	ft_printf("and ");
}

void			or(t_carry *cr)
{
	unsigned int	prm1;
	unsigned int	prm2;

	prm1 = get_param(cr, 0);
	prm2 = get_param(cr, 1);
	cr->reg[cr->cycle->descript[2]] = prm1 | prm2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	ft_printf("or ");
}

void			xor(t_carry *cr)
{
	unsigned int	prm1;
	unsigned int	prm2;

	prm1 = get_param(cr, 0);
	prm2 = get_param(cr, 1);
	cr->reg[cr->cycle->descript[2]] = prm1 ^ prm2;
	if (!cr->reg[cr->cycle->regs[2]])
		cr->carry = 1;
	else
		cr->carry = 0;
	ft_printf("xor ");
}

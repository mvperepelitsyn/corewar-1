# include "vm.h"

short	indir_position(short indir, t_carry *cr)
{
	indir %= IDX_MOD;
	check_position(indir + cr->position);
	return (indir);
}

void	rotate_or_not(t_carry *cr, unsigned char *dest, int src_i)
{
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
}

void	short_ind(unsigned char *dst, unsigned const char *src)
{
	if (ft_islitendian())
	{
		dst[1] = src[0];
		dst[0] = src[1];
	}
	else
	{
		dst[0] = src[0];
		dst[1] = src[1];
	}
}

int		display_usage()
{
	ft_printf("usage:\n\there should be an explanation\n");
	return (0);
}
//
//int		ft_err_plus(char *str, long int num, char *help_str, int toggle)
//{
//	if (toggle == 0)
//		ft_printf()
//	else
//		ft_printf("%s\n", str);
//	exit(-1);
//}

int		ft_error(char *str)
{
	if (!str)
		ft_putstr("ERROR\n");
	else
		ft_printf("%s\n", str);
	exit(-1);
}

int		check_position(int position)
{
	while (position < 0 || position >= MEM_SIZE)
	{
		if (position < 0)
			position += MEM_SIZE;
		else if (position >= MEM_SIZE)
			position -= MEM_SIZE;
	}
	return (position);
}

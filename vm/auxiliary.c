# include "vm.h"

short	indir_position(short indir, t_carry *cr)
{
	indir %= IDX_MOD;
	check_position(indir + cr->position);
	return (indir);
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

void	ft_error(char *str)
{
	if (!str)
		ft_putstr("ERROR\n");
	else
		ft_printf("%s\n", str);
	exit(69);
}

int		check_position(int position)
{
	if (position < 0)
		position += MEM_SIZE;
	else if (position >= MEM_SIZE)
		position -= MEM_SIZE;
	return (position);
}

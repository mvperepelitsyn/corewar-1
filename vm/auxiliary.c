/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:16:33 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/22 14:33:08 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

//void	short_ind(unsigned char *dst, unsigned const char *src)
//{
//	if (ft_islitendian())
//	{
//		dst[1] = src[0];
//		dst[0] = src[1];
//	}
//	else
//	{
//		dst[0] = src[0];
//		dst[1] = src[1];
//	}
//}

int		display_usage(void)
{
	ft_printf("usage:\t./corewar [-a -dump N -vis -v N]%s%s%s%s%s%s%s%s%s%s%s%s"
			, \
		" [-n N] <champ_name.cor> [-n N] <another_champ_name.cor> <...>", \
		"\n\t-a\t  : Prints output from \"aff\" (Default is to hide it)", \
		"\n\t-dump N\t  : Dumps memory after N cycles then exits", \
		"\n\t-vis\t  : Console visualization mode", \
		"\n\t-v N\t  : Verbosity levels, can be added together to enable severa"
  "l", \
  "\n\t\t    - 0 : Show only essentials", \
  "\n\t\t    - 1 : Show lives", \
  "\n\t\t    - 2 : Show cycles", \
  "\n\t\t    - 4 : Show operations (Params are NOT letteral ...)", \
  "\n\t\t    - 8 : Show deaths", \
  "\n\t\t    - 16 : Show PC movements (Except for jumps)", \
  "\n\t-n N\t  : Sets the number of the next player\n");
	return (0);
}

int		ft_err_plus(char *str, long int num, char *hlp_str, int toggle)
{
	if (toggle == 0)
		ft_printf(str, num);
	else if (toggle == 1)
		ft_printf(str, hlp_str);
	else if (toggle == 2)
		ft_printf(str, hlp_str, num);
	else
		ft_putstr("ERROR!\n");
	exit(69);
}

int		ft_error(char *str)
{
	if (!str)
		ft_putstr("ERROR\n");
	else
		ft_printf("%s\n", str);
	exit(69);
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

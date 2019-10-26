/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:12:12 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/22 14:12:14 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		check_magic_header(int fd, char *file_name)
{
	unsigned char	*rd_mag;
	unsigned char	*cnst_mag;
	unsigned int	cnst_int_mag;
	int				i;

	i = 0;
	if (!(rd_mag = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4)))
		ft_error("Error! Malloc couldn't allocate the memory!");
	if ((read(fd, rd_mag, 4)) < 0)
		ft_err_plus("Error! There is nothing to read from %s file!\n", 0,
					file_name, 1);
	cnst_int_mag = COREWAR_EXEC_MAGIC;
	if (ft_islitendian())
		cnst_int_mag = ft_reverseint(cnst_int_mag);
	cnst_mag = (unsigned char *)&cnst_int_mag;
	while (i <= 3)
	{
		if (rd_mag[i] != cnst_mag[i])
			ft_err_plus("Error! Wrong magic header in %s file!\n", 0,
						file_name, 1);
		i++;
	}
	free(rd_mag);
}

void		check_num(t_process *champs, int num, char *champ_name)
{
	int i;

	i = 0;
	if (!champ_name)
		ft_error("Error! There is no champ! What the heck is that?! That's actu"
"ally illegal! Today's without ticket, but be careful next time!");
	if (num > MAX_PLAYERS)
		ft_err_plus("Error! Wrong number for the champion %s! The number %d is "
"bigger than MAX_PLAYERS! Come down to Earth and change it!\n", num, champ_name,
2);
	if (num < 1)
		ft_err_plus("Error! Wrong number for the champion %s! The number %d is "
"too small! Don't be silly, change it!\n", num, champ_name, 2);
	while (i < MAX_PLAYERS)
	{
		if (champs[i].cmp_nbr == num)
			ft_err_plus("Error! Wrong number for the champion %s! The number %d"
" is a duplicate! Be more creative next time, silly!\n", num, champ_name, 2);
		i++;
	}
}

static void	check_file_type(char *file_name)
{
	int		i;
	char	*tmp;

	i = ft_strlen(file_name);
	tmp = ft_strsub(file_name, i - 4, 4);
	if (!ft_strequ(tmp, ".cor"))
		ft_err_plus("Error! Champion %s has wrong type! Bring me a true hero!\n"
				, 0, file_name, 1);
	ft_strdel(&tmp);
}

void		check_file_and_fill(char *file_name, t_process *chmp, int num)
{
	int		i;

	check_file_type(file_name);
	i = 0;
	if (num != 0)
	{
		chmp[num - 1].cmp_nbr = num;
		fill_the_champ(&chmp[num - 1], file_name);
	}
	else
	{
		while (i < MAX_PLAYERS)
		{
			if (chmp[i].cmp_nbr == 0)
			{
				chmp[i].cmp_nbr = i + 1;
				fill_the_champ(&chmp[i], file_name);
				break ;
			}
			i++;
		}
		if (i == MAX_PLAYERS)
			ft_error("Error! Too many champs!");
	}
}

void		how_many_champs(t_vm *vm)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->processes[i].cmp_nbr > 0)
			j++;
		i++;
	}
	if (j == 0)
		ft_error("Error! There are no champions!");
	vm->champs_count = j;
}

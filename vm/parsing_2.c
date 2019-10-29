/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:12:02 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/10/25 16:06:31 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	fill_the_name_champ(t_process *chmp, int fd, char *file_name)
{
	unsigned char	*champ_name;
	char			*name_null;

	if (!(champ_name = (unsigned char *)ft_memalloc(sizeof(unsigned char) *
			PROG_NAME_LENGTH + 1)))
		ft_error("Error! Malloc couldn't allocate the memory!");
	if (read(fd, champ_name, PROG_NAME_LENGTH) < 0)
		ft_err_plus("Error! There is no name in %s file!\n", 0, file_name, 1);
	chmp->cmp_name = ft_strsub((char *)champ_name, 0,
			ft_strlen((char *)champ_name));
	ft_strdel((char **)&champ_name);
	if (!(champ_name = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4)))
		ft_error("Error! Malloc couldn't allocate the memory!");
	if (read(fd, champ_name, 4) < 0)
		ft_err_plus("Error! There is no NULL after name in %s file!\n", 0,
				file_name, 1);
	name_null = ft_strsub((char *)champ_name, 0, 4);
	if (name_null != NULL)
		ft_err_plus("Error! There is no NULL after name in %s file!\n", 0,
				file_name, 1);
	ft_strdel(&name_null);
	ft_strdel((char **)&champ_name);
}

static void	fill_the_code_size(t_process *chmp, int fd, char *file_name)
{
	unsigned char	*rd_code_size;

	if (!(rd_code_size = (unsigned char *)ft_memalloc(sizeof(unsigned char) *
			4)))
		ft_error("Error! Malloc couldn't allocate the memory!");
	if (read(fd, rd_code_size, 4) < 0)
		ft_err_plus("Error! There is nothing instead of the size of executable "
					"code for champion %s!\n", 0, file_name, 1);
	chmp->code_size = ((size_t *)rd_code_size)[0];
	if (ft_islitendian())
		chmp->code_size = ft_reverseint(chmp->code_size);
	if (chmp->code_size > CHAMP_MAX_SIZE)
		ft_err_plus("Error! The champion %s has code size bigger than CHAMP_"
					"MAX_SIZE!\n", 0, file_name, 1);
	if (chmp->code_size == 0)
		ft_err_plus("Error! The champion %s has code size too small to be a cha"
"mp! Don't forget to feed your champ, silly human!\n", 0, file_name, 1);
	ft_strdel((char **)(&rd_code_size));
}

static void	fill_the_comment(t_process *chmp, int fd, char *file_name)
{
	unsigned char	*champ_comment;
	char			*comment_null;

	if (!(champ_comment = (unsigned char *)ft_memalloc(sizeof(unsigned char) *
			COMMENT_LENGTH + 1)))
		ft_error("Error! Malloc couldn't allocate the memory!");
	if (read(fd, champ_comment, COMMENT_LENGTH) < 0)
		ft_err_plus("Error! There is no comment in %s champion! Explain yoursel"
"f!\n", 0, file_name, 1);
	chmp->cmp_cmnt = ft_strsub((char *)champ_comment, 0,
			ft_strlen((char *)champ_comment));
	ft_strdel((char **)&champ_comment);
	if (!(champ_comment = (unsigned char *)ft_memalloc(sizeof(unsigned char) *
			4)))
		ft_error("Malloc couldn't allocate the memory!");
	if (read(fd, champ_comment, 4) < 0)
		ft_err_plus("Error! There is no NULL after comment in %s file!\n", 0,
				file_name, 1);
	comment_null = ft_strsub((char *)champ_comment, 0, 4);
	if (comment_null != NULL)
		ft_err_plus("Error! There is no NULL after comment in %s file!\n", 0,
				file_name, 1);
	ft_strdel(&comment_null);
	ft_strdel((char **)&champ_comment);
}

static void	fill_the_code(t_process *chmp, int fd, char *file_name)
{
	char	*test;
	ssize_t check_read;

	if (!(chmp->code = (unsigned char *)ft_memalloc(sizeof(unsigned char) *
			chmp->code_size)))
		ft_error("Error! Malloc couldn't allocate the memory!");
	check_read = read(fd, chmp->code, chmp->code_size);
	if (check_read < 0)
		ft_err_plus("Error! There is no executable code to read for the champio"
"n %s! Didn't you forget your head at home?\n", 0, file_name, 1);
	else if (check_read != chmp->code_size)
		ft_err_plus("Error! Executable code for the champion %s is smaller than"
" it should be! Train your champion harder!\n", 0, file_name, 1);
	test = ft_strnew(1);
	if (read(fd, test, 1) > 0)
		ft_err_plus("Error! There is something else after executable code for c"
"hampion %s! Please, make this champion lose some weight!\n", 0, file_name, 1);
	ft_strdel(&test);
}

void		fill_the_champ(t_process *chmp, char *file_name)
{
	int		fd;
	char	*clion_file;

	clion_file = ft_strjoin("../", file_name);
	if ((fd = open(clion_file, O_RDONLY)) < 0)
		if ((fd = open(file_name, O_RDONLY)) < 0)
			ft_err_plus("Error! There is nothing to open from champion %s! Cons"
			   "ider to create your champion at very least!\n", 0, file_name,
			   1);
	check_magic_header(fd, file_name);
	fill_the_name_champ(chmp, fd, file_name);
	fill_the_code_size(chmp, fd, file_name);
	fill_the_comment(chmp, fd, file_name);
	fill_the_code(chmp, fd, file_name);

	ft_strdel(&clion_file);
}

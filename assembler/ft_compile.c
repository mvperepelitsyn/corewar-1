/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:57:42 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/17 17:52:34 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		g_temp = 0;

void	ft_code_create(t_asm_data *asm_data, int fd)
{
	int		i;

	i = 0;
	ft_add_magic_header(fd, &i);
	ft_add_name(asm_data, fd, &i, -1);
	ft_add_null(&i, fd);
	ft_add_code_size(asm_data, fd, &i);
	ft_add_comment(asm_data, fd, &i, -1);
	ft_add_null(&i, fd);
	ft_code_compile(asm_data, fd, &i);
}

void	ft_convert_to_binary(t_asm_data *asm_data, char *name)
{
	int		fd;
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	if (name[i] == '.' && ft_strlen(name) > 5)
		i++;
	while (ft_strlen(name + i) != 2)
		i++;
	temp = ft_strsub(name, 0, i);
	str = ft_strjoin_orig(temp, ".cor");
	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 3)
		exit(ft_printf("cant't create file %s\n", str));
	ft_code_create(asm_data, fd);
	close(fd);
	ft_printf("Writing output program to %s\n", str);
	free(str);
	free(temp);
}

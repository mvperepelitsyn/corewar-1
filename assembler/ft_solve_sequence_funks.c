/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_sequence_funks.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:07:27 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/29 16:36:59 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	ft_check_last_row(t_asm_data *asm_data, int fd, int i)
{
	char		*str;
	t_list		*chain;
	t_token		*token;

	i = asm_data->count_symbols / 2;
	str = ft_strnew(i + 50);
	lseek(fd, (off_t)(i), 0);
	i = read(fd, str, i + 45);
	str[i] = '\0';
	while (str[i] == 0 || str[i] == ' ' || str[i] == '\t')
		i--;
	if (str[i] == '\n')
		ft_add_new_str_token(asm_data);
	else
		ft_error_add(asm_data, ft_strdup("Add newline after last row "), 0, 2);
	free(str);
}

void	ft_check_main_params_exists(t_asm_data *asm_data)
{
	if (!(MACHINE_NAME_COMMENT & 1))
		ft_error_add(asm_data, ft_strdup("No Champ's name founded "), 0, 3);
	if (!(MACHINE_NAME_COMMENT & 2))
		ft_error_add(asm_data, ft_strdup("No Champ's comment founded "), 0, 3);
	if (!MACHINE_VALID_CODE)
		ft_error_add(asm_data, ft_strdup("No commands were founed. Add one "),\
		0, 3);
}

void	ft_row_wrapper(t_syntax_row *row)
{
	ROW_WAIT_SEP = 1;
	ROW_CNT_ARG++;
}

void	ft_fill_asm_synt_row(t_asm_data *asm_data)
{
	ASM_SYNTAX_ROW = ft_lstnew(NULL, (sizeof(t_syntax_row)));
	ASM_SYNTAX_ROW->content = ft_syn_row_init();
}

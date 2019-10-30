/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:09:38 by thansen           #+#    #+#             */
/*   Updated: 2019/10/30 16:09:39 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_asm.h"
#include "asm_error.h"

char	*get_token_content(t_parser *parser, const char *row, unsigned start)
{
	char	*content;

	if (!(content = ft_strsub(row, start, parser->column - start)))
		terminate(ERR_STR_INIT);
	return (content);
}

char	*join_str(char **str1, char **str2)
{
	char *result;

	if (!(result = ft_strjoin(*str1, *str2)))
		terminate(ERR_STR_INIT);
	ft_strdel(str1);
	ft_strdel(str2);
	return (result);
}

void	update_parser_position(t_parser *parser, const char *row)
{
	unsigned i;

	i = ++(parser->column);
	while (row[i] && row[i] != '\"')
	{
		if (row[i] == '\n')
		{
			parser->row++;
			parser->column = 0;
		}
		else
			parser->column++;
		i++;
	}
}

void	update_row(char **row, char *ptr)
{
	char *new;

	if (!(new = ft_strdup(ptr)))
		terminate(ERR_STR_INIT);
	ft_strdel(row);
	*row = new;
}

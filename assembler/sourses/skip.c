/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:10:38 by thansen           #+#    #+#             */
/*   Updated: 2019/10/30 16:10:39 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_asm.h"

void	skip_whitespaces(t_parser *parser, const char *row)
{
	while (is_whitespace(row[parser->column]))
		parser->column++;
}

void	skip_comment(t_parser *parser, const char *row)
{
	if (row[parser->column] == COMMENT_CHAR
		|| row[parser->column] == ALT_COMMENT_CHAR)
		while (row[parser->column] && row[parser->column] != '\n')
			parser->column++;
}

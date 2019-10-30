/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:42 by thansen           #+#    #+#             */
/*   Updated: 2019/10/30 16:07:46 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_asm.h"
#include "asm_error.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

void	assemble(char *filename)
{
	int			fd;
	t_parser	*parser;
	t_token		*current;

	if ((fd = open(filename, O_RDONLY)) == -1)
		terminate(ERR_OPEN_FILE);
	parser = init_asm_parser(fd);
	parse_asm(parser);
	current = parser->tokens;
	process_info(parser, &current);
	process_asm_code(parser, &current);
	replace_mentions(parser);
	filename = replace_extension(filename, ".s", ".cor");
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		terminate(ERR_CREATE_FILE);
	write_bytecode_file(fd, parser);
	ft_printf("Writing output program to %s\n", filename);
	ft_strdel(&filename);
	free_asm_parser(&parser);
}

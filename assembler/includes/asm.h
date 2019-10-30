/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:12:05 by thansen           #+#    #+#             */
/*   Updated: 2019/10/30 16:12:53 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"

void	assemble(char *filename);

void	disassemble(char *filename);

/*
** Filename
*/

t_bool	is_filename(const char *filename, const char *ext);

char	*replace_extension(char *filename, char *old, char *new);

/*
** Print
*/

void	print_help(void);

/*
** Utils
*/

void	terminate(char *s);

#endif

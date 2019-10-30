# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/29 21:37:44 by thansen           #+#    #+#              #
#    Updated: 2019/10/30 16:00:15 by ggerhold         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_NAME = ../asm

CC = gcc
FLAGS = -Wall -Werror -Wextra

# Libraries and Includes

ASM_LIBRARIES = -lftprintf -L$(FT_PRINTF_DIRECTORY)
ASM_INCLUDES = \
	-I$(HEADERS_DIRECTORY)\
	-I$(LIBFT_HEADERS)\
	-I$(FT_PRINTF_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./ft_printf/libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

FT_PRINTF = $(FT_PRINTF_DIRECTORY)libftprintf.a
FT_PRINTF_DIRECTORY = ./ft_printf/
FT_PRINTF_HEADERS = $(FT_PRINTF_DIRECTORY)includes/

HEADERS_DIRECTORY = ./includes/

ASM_HEADERS_LIST = \
	op.h\
	asm.h\
	asm_error.h\
	asm_asm.h
ASM_HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(ASM_HEADERS_LIST))

# Sources

ASM_SOURCES_DIRECTORY = ./assembler/
ASM_SOURCES_LIST = \
	asm.c\
	filename.c\
	print.c\
	utils.c\
	assemble.c\
	init.c\
	get_row.c\
	parse.c\
	parse_is.c\
	parse_utils.c\
	skip.c\
	token.c\
	process_info.c\
	process_code.c\
	process_code_utils.c\
	process_arg.c\
	label.c\
	write.c\
	free.c\
	error.c\
	error_info.c

ASM_SOURCES = $(addprefix $(ASM_SOURCES_DIRECTORY), $(ASM_SOURCES_LIST))

# Objects

OBJECTS_DIRECTORY = ./assembler/objects/

# asm

ASM_OBJECTS_DIRECTORY = $(OBJECTS_DIRECTORY)
ASM_OBJECTS_LIST = $(patsubst %.c, %.o, $(ASM_SOURCES_LIST))
ASM_OBJECTS	= $(addprefix $(ASM_OBJECTS_DIRECTORY), $(ASM_OBJECTS_LIST))

.PHONY: all clean fclean re

all: $(ASM_NAME)

$(ASM_NAME): $(FT_PRINTF) $(ASM_OBJECTS_DIRECTORY) $(ASM_OBJECTS)
	@$(CC) $(FLAGS) $(ASM_LIBRARIES) $(ASM_INCLUDES) $(ASM_OBJECTS) -o $(ASM_NAME)

$(ASM_OBJECTS_DIRECTORY):
	@mkdir -p $(ASM_OBJECTS_DIRECTORY)

$(ASM_OBJECTS_DIRECTORY)%.o : $(ASM_SOURCES_DIRECTORY)%.c $(ASM_HEADERS)
	@$(CC) $(FLAGS) -c $(ASM_INCLUDES) $< -o $@

$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIRECTORY)

clean:
	@$(MAKE) -C $(FT_PRINTF_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	@$(MAKE) -C $(FT_PRINTF_DIRECTORY) fclean
	@rm -f $(ASM_NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thansen <thansen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 18:13:41 by ggerhold          #+#    #+#              #
#    Updated: 2019/10/27 18:11:05 by thansen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc -ggdb
CC_FLAGS= -Wall -Wextra -Werror -g#remove the flag
NAME_ASM = ../asm
LIB_DIR = ./libft/includes
HEADERDIR = ../
OBJ_DIR = ./obj-asm
SRC = main.c ft_asm_structs_init.c ft_error_manager.c ft_champ_name_comment.c \
	ft_lexer_champ_code.c ft_fill_tokens.c ft_fill_tokens_newline_and_direct.c \
	ft_lexer_champ_code_helpers.c ft_check_syntax.c ft_champ_name_comment_extend.c \
	ft_table_of_operations.c ft_create_rows.c ft_solve_sequence_funks.c ft_check_syntax_helpers.c \
	ft_compile.c ft_conver_words.c ft_compile_helpers.c ft_convert_code.c ft_convert_args.c \
	ft_convert_helpers.c ft_clear_data.c tools.c
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

LIB=./libft/libft.a

all: $(NAME_ASM)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME_ASM):  $(OBJ_DIR) $(OBJ)
	@make -C ./libft/
	@make -C ./libft/ clean
	@$(CC) $(CC_FLAGS) $(OBJ) $(LIB) -I $(LIB_DIR) -I ../ -o $(NAME_ASM)

$(OBJ_DIR)/%.o: ./%.c
	@$(CC) $(FLAGS) -c $< -I$(INC_DIR) -I$(LIBFT_H) -o $@

clean:
	@rm -rf *.o

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME_ASM)
	@rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re

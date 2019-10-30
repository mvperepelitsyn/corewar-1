# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 20:04:56 by dfrost-a          #+#    #+#              #
#    Updated: 2019/10/30 20:05:16 by dfrost-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

HEAD = ./
SRC = vm.c vm_init.c auxiliary.c parsing.c game.c check_operation.c commands.c \
commands_utilities.c console_vis.c andorxor_cmds.c ld_ldi_lld_lldi_cmds.c \
commands_2.c commands_utilities_2.c game_2.c parsing_2.c parsing_3.c sti_cmd.c \
parsing_4.c console_vis_2.c

OBJ = $(addprefix $(OBJPATH)/,$(SRC:.c=.o))
OBJPATH = ./objects

FLAGS = -g -Wall -Wextra -Werror
LIB = -L ./libft -lft
LIBPATH = ./libft

all: $(NAME)

$(NAME):  $(OBJPATH) $(OBJ)
	@make -C $(LIBPATH)
	@gcc $(FLAGS) $(OBJ) -o $(NAME) -I $(HEAD) $(LIB)

$(OBJPATH):
	@mkdir -p $(OBJPATH)

$(OBJPATH)/%.o: %.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBPATH) clean
	@/bin/rm -rf $(OBJPATH)

fclean: clean
	@make -C $(LIBPATH) fclean
	@/bin/rm -f $(NAME)

re: fclean all

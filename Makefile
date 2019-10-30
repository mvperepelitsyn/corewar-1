# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:31:29 by ggerhold          #+#    #+#              #
#    Updated: 2019/10/30 20:02:58 by dfrost-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED:="\033[1;31m"
GREEN:="\033[1;32m"

all:
	@make -C assembler
	@echo $(GREEN) "-> making assembler"
	@make -C vm
	@echo $(GREEN) "-> making vm"m

clean:
	@make -C assembler clean
	@echo $(RED) "-> cleaning assembler"
	@make -C vm clean
	@echo $(RED) "-> cleaning vm"

fclean:
	@make -C assembler fclean
	@echo $(RED) "-> fcleaning assembler"
	@make -C vm fclean
	@echo $(RED) "-> fcleaning vm"

re: fclean all

.PHONY: all clean fclean re
=======

re: fclean all

.PHONY: all clean fclean re

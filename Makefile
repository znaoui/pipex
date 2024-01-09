# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znaoui <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 14:06:35 by znaoui            #+#    #+#              #
#    Updated: 2022/10/25 14:56:54 by znaoui           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############### SETUP ###############

NAME = pipex

CFLAGS = -Wall -Wextra -Werror -g3

SRCS = srcs/utils_pipex.c srcs/ft_strjoin.c srcs/ft_strnstr.c srcs/ft_split.c srcs/pipex.c

OBJS = $(SRCS:.c=.o)

############### COMMANDS ###############

all:
	@make --no-print-directory ${NAME}

.c.o:
	@gcc ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@gcc ${CFLAGS} -o ${NAME} ${OBJS}
	@echo "$(WHITE)Compilation in progress..$(DEFAULT)"
	@sleep 1
	@echo "$(GREEN)The program ${NAME} is ready!$(DEFAULT)"

help: 
	@echo "$(WHITE)Commands available: all, clean, fclean, re$(DEFAULT)"

clean:
	@rm -rf ${OBJS}
	@echo "$(YELLOW)All object files have been deleted$(DEFAULT)"

fclean: clean
	@rm -rf ${NAME}
	@echo "$(RED)The program ${NAME} has been deleted$(DEFAULT)"

re: fclean
	@make --no-print-directory all

.PHONY : all help clean fclean re

.SILENT: 

############### COLORS ##############

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
WHITE = \033[1;37m

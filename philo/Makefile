# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 12:49:00 by omer/baha         #+#    #+#              #
#    Updated: 2023/10/07 13:25:50 by omer/baha        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = src/main.c src/utils.c src/philo.c src/init.c
OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME} 
	@echo "\n\n${GREEN}COMPILATION HAS DONE!${DEFAULT}\n\n"
	@echo "${CYAN}./$(NAME) [philo number] [die time] [eat time] [sleep time] [eat goal(optional)]${DEFAULT}\n\n"

%.o: %.c
	@ ${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\n\n${RED}Objective files are being deleted...${DEFAULT}\n\n"
	@rm -rf ${OBJ}

fclean:
	@echo "\n\n${RED}Objective files and executable are being deleted...${DEFAULT}\n\n"
	@rm -rf ${OBJ} ${NAME}

re: fclean all

norm:
	@echo "\n\n${YELLOW}The norm is being checked...\n\n"
	@norminette ${SRC} includes/philo.h
	@echo "${DEFAULT}"

PHONY.: all clean fclean re 
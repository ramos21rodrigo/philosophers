# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roramos <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 15:04:30 by roramos           #+#    #+#              #
#    Updated: 2023/01/05 17:00:02 by roramos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = srcs/philo.c\
		srcs/args.c\
		srcs/throwerror.c
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME} -lpthread

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

all: ${NAME}

re: fclean all

.PHONY: ${NAME} all clean fclean re

.SILENT:
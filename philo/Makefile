# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roramos <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 15:04:30 by roramos           #+#    #+#              #
#    Updated: 2023/01/14 15:10:32 by roramos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS =	srcs/actions.c\
		srcs/args.c\
		srcs/display_status.c\
		srcs/init_philos.c\
		srcs/philo.c\
		srcs/pthreads.c\
		srcs/throwerror.c\
		srcs/time.c
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
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 18:54:49 by erigonza          #+#    #+#              #
#    Updated: 2024/08/26 17:41:29 by erigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo.c utils.c
DIR_SRC = ./src
DIR_OBJ = $(DIR_SRC)/obj
OBJS = $(addprefix $(DIR_OBJ)/, $(SRCS:.c=.o))
NAME	= philo

RM		 = rm -fr

INC = -I ./inc/

CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address

CC = gcc

all:		dir ${NAME}

dir: 
				mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c Makefile ./inc/philo.h
				$(CC) $(FLAGS) $(INC)  -c $< -o $@
				clear

${NAME}:	${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME} $(INC)
				clear

c clean:
				${RM} ${OBJS}
				clear

f fclean:		clean
				${RM} ${NAME} ${DIR_OBJ}
				clear

r re:			fclean all

.PHONY:		clean fclean re all
.SILENT:

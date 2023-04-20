# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 14:51:37 by mleitner          #+#    #+#              #
#    Updated: 2023/04/20 21:06:25 by mleitner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell
CC				:= cc
RM		    	:= rm -f
FLAGS			:= -Wall -Wextra -Werror
DEBUG			:= -g

SRCSDIR			:= ./src/
SRCSLIST		:= main.c
SRCS			:= $(addprefix ${SRCSDIR}, ${SRCSLIST})
HEADDIR			:= ./inc/

OBJSDIR			:= ./obj/
OBJSLIST		:= ${SRCSLIST:.c=.o}
OBJS			:= $(addprefix ${OBJSDIR}, ${OBJSLIST})

LIBFTDIR		:= ./libft/
LIBFT			:= ${LIBFTDIR}libft.a

LIBS			:= -L${LIBFTDIR} -lft -lreadline
INCS			:= -I${HEADDIR} -I${LIBFTDIR}

${NAME}:		${LIBFT} ${OBJSDIR} ${OBJS}
				${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${LIBS} ${INCS}

${LIBFT}:
				make -C ${LIBFTDIR}

${OBJSDIR}%.o:	${SRCSDIR}%.c
				${CC} ${FLAGS} ${DEBUG} ${INCS} -c $< -o $@

${OBJSDIR}:
				mkdir -p ${OBJSDIR}

.PHONY:			all clean fclean re

all:			${NAME}

clean:
				${RM} -r ${OBJSDIR}
				make -C ${LIBFTDIR} clean

fclean:			clean
				${RM} ${NAME}
				make -C ${LIBFTDIR} fclean

re:				fclean all
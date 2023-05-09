# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmocsai <rmocsai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 14:51:37 by mleitner          #+#    #+#              #
#    Updated: 2023/05/09 13:13:20 by rmocsai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell
CC				:= cc
RM		    	:= rm -f
FLAGS			:= -Wall -Wextra -Werror
DEBUG			:= -g

SRCSDIR			:= ./src/
SUBDIRS			:= 	./obj/env \
					./obj/builtins \
					
SRCSLIST		:=	main.c \
					env/envcpy.c \
					env/list_func.c \
					env/list_func2.c \
					signals.c \
					builtins/builtins.c \
					temp_tester.c \

					
SRCS			:= $(addprefix ${SRCSDIR}, ${SRCSLIST})
HEADDIR			:= ./inc/

OBJSDIR			:= ./obj/
OBJSLIST		:= ${SRCSLIST:.c=.o}
OBJS			:= $(addprefix ${OBJSDIR}, ${OBJSLIST})

LIBFTDIR		:= ./libft/
LIBFT			:= ${LIBFTDIR}libft.a

LIBS			:= -L${LIBFTDIR} -lft -lreadline
INCS			:= -I${HEADDIR} -I${LIBFTDIR}

YELLOW			:= \033[1;33m
CLR_RM			:= \033[0m

${NAME}:		${LIBFT} ${OBJSDIR} ${OBJS}
				${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${LIBS} ${INCS}
				@echo "${YELLOW}${NAME} ${CLR_RM}created ✔️"

${LIBFT}:
				make -C ${LIBFTDIR}

${OBJSDIR}%.o:	${SRCSDIR}%.c
				${CC} ${FLAGS} ${DEBUG} ${INCS} -c $< -o $@

${OBJSDIR}:
				mkdir -p ${OBJSDIR} ${SUBDIRS}

.PHONY:			all clean fclean re

all:			${NAME}

clean:
				${RM} -r ${OBJSDIR}
				make -C ${LIBFTDIR} clean

fclean:			clean
				${RM} ${NAME}
				make -C ${LIBFTDIR} fclean

re:				fclean all
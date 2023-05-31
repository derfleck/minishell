NAME			:= minishell
CC				:= cc
RM		    	:= rm -f
FLAGS			:= -Wall -Wextra -Werror
DEBUG			:= -g
SRCSDIR			:= ./src/

SUBDIRS			:= 	./obj/env \
					./obj/builtins \
					./obj/exit \
					./obj/lexer \
					./obj/parser \
					./obj/heredoc \
					./obj/executor \
					./obj/expander
					
SRCSLIST		:=	main.c \
					env/envcpy.c \
					env/list_func.c \
					env/list_func2.c \
					env/list_func3.c \
					env/list_to_arr.c \
					signals.c \
					builtins/1_pwd.c \
					builtins/2_cd.c \
					builtins/3_export_unset.c \
					builtins/4_exit.c \
					builtins/5_echo.c \
					temp_tester.c \
					exit/exit1.c \
					utils.c \
					lexer/lexer.c \
					lexer/list.c \
					lexer/split.c \
					parser/parser_start.c \
					parser/parser_input.c \
					heredoc/heredoc.c \
					executor/exec.c \
					executor/utils.c \
					executor/open_check.c \
					executor/search_path.c \
					executor/exec_multiple.c \
					expander/expand1.c \
					expander/expand2.c \
					expander/expand3.c \
					expander/expand4.c 
										
SRCS			:= $(addprefix ${SRCSDIR}, ${SRCSLIST})
HEADDIR			:= ./inc/

OBJSDIR			:= ./obj/
OBJSSUB			:= ./obj/lexer/ \
					./obj/parser/ \
					./obj/heredoc \
					./obj/executor

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
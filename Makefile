##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

SRC	= 	src/main.c					\
		src/loop.c					\
		src/prompt.c					\
		src/concat_exec.c				\
		src/built_ins/check_built_ins.c			\
		src/built_ins/cd.c				\
		src/built_ins/exit.c				\
		src/built_ins/setenv.c				\
		src/built_ins/unsetenv.c			\
		src/built_ins/env.c				\
		src/built_ins/echo.c				\
		src/linked_list.c				\
		src/exec.c					\
		src/get_env_var.c				\
		src/verif_env.c					\
		src/check_segfault.c				\
		src/create_env.c				\
		src/pwd_changes.c				\
		src/binary_tree.c				\
		src/parser/parsing_cmd.c			\
		src/parser/parsing_pipes_and_redirections.c	\
		src/parser/error_handling.c			\
		src/set_pipefd.c				\
		src/exec_tree/exec_tree.c			\
		src/exec_tree/exec_pipe.c			\
		src/exec_tree/exec_redirect.c			\
		src/exec_tree/exec_separator.c			\
		src/exec_tree/exec_double_left_redirect.c	\
		src/parser/globbing/brackets.c			\
		src/parser/globbing/glob.c			\
		src/parser/globbing/interrogation.c		\
		src/parser/globbing/wildcard/wildcard.c		\
		src/parser/globbing/wildcard/wildcard_parser.c	\

OBJ	=	$(SRC:.c=.o)

CC	= 	gcc -Wextra -Wall -Werror -g3 -no-pie

_END=$'\x1b[0m'
_RED=$'\x1b[31m'

NO_OF_FILES 	:=	 $(words $(SRC))

NAME		=	42sh

LIB_NAME	=	libmy.a

FLAGS		=	-L./lib/my -lmy

CFLAGS		=	-I./include

all:	prepare_lib $(NAME)

prepare_lib:
	make -C lib/my

$(NAME):	$(OBJ)
	@ echo "\033[1;36m[ FILES COMPILED ] \033[0m \033[1;35m$(NO_OF_FILES)\033[0m"
	$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(CFLAGS)
	@ echo "\033[1;35m ------------------Name of Binary : \033[1;31m$(NAME)\033[0;31m®\033[1;35m Created Sucesfully ------------------\033[0m"

clean:
	make clean -C lib/my
	rm -f $(OBJ)

fclean:	clean
	rm -f lib/my/$(LIB_NAME)
	rm -f $(NAME)

re:	fclean all

%.o:	%.c
	@ echo "\033[1;35m[ OK ]\033[0m Compiling" $<
	@ $(CC) -o $@ -c $< $(CFLAGS)

.SILENT:
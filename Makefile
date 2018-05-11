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

OBJ	=	$(SRC:.c=.o)

CC	= 	gcc -Wextra -Wall -Werror -g3 -no-pie

NAME	=	42sh

LIB_NAME	=	libmy.a

FLAGS	=	-L./lib/my -lmy

CFLAGS	=	-I./include

all:	prepare_lib $(NAME)

prepare_lib:
	make -C lib/my

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(CFLAGS)

clean:
	make clean -C lib/my
	rm -f $(OBJ)

fclean:	clean
	rm -f lib/my/$(LIB_NAME)
	rm -f $(NAME)

re:	fclean all

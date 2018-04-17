##
## EPITECH PROJECT, 2017
## Makefile mysh
## File description:
## Makefile mysh
##

SRCS	=	main.c                  \
            my_str_to_word_array.c  \
            search_envp.c           \
            my_strcmp.c

CFLAGS	=	-W -Wall -Wextra -I. -g3 -L. -lgnl

OBJ	=	$(SRCS:.c=.o)

NAME	=	mysh

all:
	cp /usr/bin/tcsh 42sh

clean:
	rm -f *.o

fclean: clean

re: 	all fclean

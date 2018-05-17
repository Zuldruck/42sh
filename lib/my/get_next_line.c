/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2017
** File description:
** CPE_getnextline_2017 made by Sanchez Lucas
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


char *get_next_line(int fd)
{
	__ssize_t left = 0;
	size_t buff_size = 10;
	char *input = NULL;
	FILE *fd_open = fdopen(fd, "r");

	left = getline(&input, &buff_size, fd_open);
	if (left == -1) {
		free(input);
		return (NULL);
	}
	if (input[left - 1] == 10)
		input[left - 1] = 0;
	return (input);
}

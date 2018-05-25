/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int count_loop_foreach(char **str)
{
	int i = 0;
	int len = 0;

	while (str[i]) {
		if (strcmp(str[i], "(") == 0 || strcmp(str[i], ")") == 0) {
			i++;
			continue;
		}
		len++;
		i++;
	}
	return (len - 2);
}
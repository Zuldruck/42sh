/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int is_alpha_string(char *str)
{
	if (!str)
		return (1);
	for (int i = 0 ; str[i] ; i++)
		if (is_alpha(str[i]) == 1)
			return (1);
	return (0);
}

int check_error_handling_repeat(char **str)
{
	if (is_alpha_string(str[1]) == 1) {
		printf("repeat: Badly formed number.\n");
		return (1);
	}
	if (my_tablen(str) < 3) {
		printf("repeat: Too few arguments.\n");
		return (1);
	}
	return (0);
}

int repeat(char **str, env_t *env, int *ret_value)
{
	if (!str || !env) {
		*ret_value = 1;
		return (84);
	}
	if (check_error_handling_repeat(str) != 0) {
		*ret_value = 1;
		return (84);
	}
	return (0);
}

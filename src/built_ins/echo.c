/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** echo
*/

#include "42sh.h"

void process_args_echo(char **str)
{
	for (int i = 1 ; str[i] ; i++) {
		if (str[i]) {
			my_printf("%s", str[i]);
			(str[i + 1] != NULL ? write(1, " ", 1) : 0);
		}
	}
}

void echo_func(char **str, __attribute__((unused))env_t *env, int *ret_value)
{
	if (!str) {
		*ret_value = 84;
		return;
	} else if (str && !str[1]) {
		my_printf("\n");
		*ret_value = 0;
		return;
	}
	process_args_echo(str);
	write(1, "\n", 1);
}
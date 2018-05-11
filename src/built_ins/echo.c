/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** echo
*/

#include "42sh.h"

int is_a_env_value(env_t *env, char *str)
{
	if (get_env(env, str + 1) == NULL)
		return (0);
	return (1);
}

int check_undefined_variable(char **str, env_t *env)
{
	for (int i = 1 ; str[i] ; i++)
		if (str[i][0] == '$' && is_a_env_value(env, str[i]) == 0) {
			my_printf("%s: Undefined variable.\n", str[i] + 1);
			return (1);
		}
	return (0);
}

void process_args_echo(char **str, env_t *env)
{
	for (int i = 1 ; str[i] ; i++) {
		if (str[i][0] == '$') {
			my_printf("%s", get_env(env, str[i] + 1));
			(str[i + 1] != NULL ? write(1, " ", 1) : 0);
		} else if (str[i] != NULL) {
			my_printf("%s", str[i]);
			(str[i + 1] != NULL ? write(1, " ", 1) : 0);
		}
	}
}

void echo_func(char **str, env_t *env, int *ret_value)
{
	if (!str) {
		*ret_value = 84;
		return;
	}
	if (str && !str[1]) {
		my_printf("\n");
		*ret_value = 0;
		return;
	}
	if (check_undefined_variable(str, env) != 0) {
		*ret_value = 1;
		return;
	}
	process_args_echo(str, env);
	write(1, "\n", 1);
}
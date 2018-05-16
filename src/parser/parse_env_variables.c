/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parse_env_variables
*/

#include "42sh.h"

int is_a_env_value(env_t *env, char *str)
{
	if (get_env(env, str + 1) == NULL)
		return (0);
	return (1);
}

int parse_env_var_in_args(char **str, env_t *env)
{
	char *new_str = NULL;

	for (int i = 0; (*str)[i]; i++) {
		if ((*str)[i] == '$' && (*str)[i + 1]
		&& !is_a_env_value(env, (*str) + i)) {
			my_printf("%s: Undefined variable.\n", (*str) + i + 1);
			return (1);
		} else if ((*str)[i] == '$' && (*str)[i + 1]) {
			new_str = strndup(*str, i);
			new_str = realloc(new_str, i + 1
			+ strlen(get_env(env, *str + i + 1)));
			strcat(new_str, get_env(env, (*str) + i + 1));
			*str = new_str;
			return (0);
		}
	}
	return (0);
}

int parse_env_variables(char **cmd, env_t *env, int *ret_value)
{
	for (int i = 0; cmd[i]; i++) {
		if (parse_env_var_in_args(&cmd[i], env) == 1) {
			*ret_value = 1;
			return (1);
		}
	}
	return (0);
}
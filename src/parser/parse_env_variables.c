/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parse_env_variables
*/

#include "42sh.h"

char *get_var_name(char *str)
{
	char *name = NULL;
	int i = 0;

	while (str[i] && str[i] != '"' && str[i] != '\'')
		i++;
	name = strndup(str, i);
	return (name);
}

int is_a_env_value(env_t *env, char *str)
{
	char *var_name = get_var_name(str + 1);

	if (get_env(env, var_name) == NULL) {
		free(var_name);
		return (0);
	}
	free(var_name);
	return (1);
}

char *get_str_with_env(env_t *env, char *var_name,
						char *beg_str, char **str)
{
	char *end_str = *str + strlen(beg_str) + 1 + strlen(var_name);
	char *end_with_env = my_strcat(get_env(env, var_name), end_str);
	char *ret = my_strcat(beg_str, end_with_env);

	free(*str);
	free(beg_str);
	free(var_name);
	free(end_with_env);
	return (ret);
}

int parse_env_var_in_args(char **str, env_t *env)
{
	char *new_str = NULL;
	char *var_name = NULL;

	for (int i = 0; (*str)[i]; i++) {
		if ((*str)[i] == '$' && (*str)[i + 1]
		&& !is_a_env_value(env, (*str) + i)) {
			my_printf("%s: Undefined variable.\n", (*str) + i + 1);
			return (1);
		} else if ((*str)[i] == '$' && (*str)[i + 1]) {
			var_name = get_var_name(*str + i + 1);
			new_str = strndup(*str, i);
			*str = get_str_with_env(env, var_name, new_str, str);
			return (0);
		}
	}
	return (0);
}

int parse_env_variables(char **cmd, env_t *env, int *ret_value)
{
	for (int i = 0; cmd && cmd[i]; i++) {
		if (parse_env_var_in_args(&cmd[i], env) == 1) {
			*ret_value = 1;
			return (1);
		}
	}
	return (0);
}
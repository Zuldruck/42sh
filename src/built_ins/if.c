/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int process_if(char **str, env_t *env);

int check_if(char **s, int *ret_if)
{
	int ret = 0;

	if (check_only_number(s, ret_if) == 0)
		return (1);
	if (!s[2] || !s[1] || !s[3])
		return (0);
	strcmp(s[2], ">") == 0 && strcmp(s[1], s[3]) > 0 ? ret = 1 : 0;
	strcmp(s[2], ">=") == 0 && strcmp(s[1], s[3]) >= 0 ? ret = 1 : 0;
	strcmp(s[2], "<") == 0 && strcmp(s[1], s[3]) < 0 ? ret = 1 : 0;
	strcmp(s[2], "<=") == 0 && strcmp(s[1], s[3]) <= 0 ? ret = 1 : 0;
	strcmp(s[2], "==") == 0 && strcmp(s[1], s[3]) == 0 ? ret = 1 : 0;
	strcmp(s[2], "!=") == 0 && strcmp(s[1], s[3]) != 0 ? ret = 1 : 0;
	*ret_if = 4;
	return (ret);
}

int process_if(char **str, env_t *env)
{
	int ret_value = 0;
	int ret_if = 0;

	if (check_if(str, &ret_if) != 1) {
		if (check_then_if(str, env) != 0)
			return (1);
		return (0);
	}
	check_then(str) != 0 && str[ret_if] != NULL ?
	my_exec(str + ret_if, env, (int[2]){0, 1}): 0;
	return (ret_value);
}

void if_func(char **str, shell_t shell, int *ret_value)
{
	if (!str) {
		*ret_value = 1;
		return;
	}
	if (check_error_handling_if(str) != 0) {
		*ret_value = 1;
		return;
	}
	if (process_if(str, shell.env) != 0) {
		*ret_value = 0;
		return;
	}
}
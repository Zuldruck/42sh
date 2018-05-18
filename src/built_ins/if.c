/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int check_error_handling_if(char **str)
{
	if (my_tablen(str) < 5) {
		printf("if: Empty if.\n");
		return (1);
	}
	return (0);
}

int check_if(char **s)
{
	int ret = 0;

	strcmp(s[2], ">") == 0 && strcmp(s[1], s[3]) > 0 ? ret = 1 : 0;
	strcmp(s[2], ">=") == 0 && strcmp(s[1], s[3]) >= 0 ? ret = 1 : 0;
	strcmp(s[2], "<") == 0 && strcmp(s[1], s[3]) < 0 ? ret = 1 : 0;
	strcmp(s[2], "<=") == 0 && strcmp(s[1], s[3]) <= 0 ? ret = 1 : 0;
	strcmp(s[2], "==") == 0 && strcmp(s[1], s[3]) == 0 ? ret = 1 : 0;
	strcmp(s[2], "!=") == 0 && strcmp(s[1], s[3]) != 0 ? ret = 1 : 0;
	return (ret);
}

int process_if(char **str, env_t *env)
{
	char *tmp = NULL;
	int ret_value = 0;

	if (check_if(str) != 1)
		return (0);
	tmp = convert_tab_to_string(str + 4);
	parse_cmd(env, tmp, &ret_value);
	return (ret_value);
}

void if_func(char **str,env_t *env, int *ret_value)
{
	if (!str) {
		*ret_value = 1;
		return;
	}
	if (check_error_handling_if(str) != 0) {
		*ret_value = 1;
		return;
	}
	if (process_if(str, env) != 0) {
		*ret_value = 1;
		return;
	}
}
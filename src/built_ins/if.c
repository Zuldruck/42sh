/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

static int ret_if = 0;

int check_error_handling_if(char **str)
{
	if (my_tablen(str) < 3 || my_tablen(str) < 2) {
		my_tablen(str) < 2 ?
		printf("if: Too few arguments.\n") : printf("if: Empty if.\n");
		return (1);
	}
	if (isdigit(str[1][0]) && isalpha(str[1][1])) {
		printf("if: Badly formed number.\n");
		return (1);
	}
	if (strlen(str[1]) == 1 && is_alpha_string(str[1])) {
		printf("if: Expression Syntax.\n");
		return (1);
	}
	return (0);
}

int check_only_number(char **s)
{
	if (strcmp(s[2], ">") == 0 || strcmp(s[2], ">=") == 0 ||
	strcmp(s[2], "<") == 0 || strcmp(s[2], "<=") == 0
	|| strcmp(s[2], "==") == 0 || strcmp(s[2], "!=") == 0)
		return (1);
	if (is_alpha_string(s[1]) == 0) {
		ret_if = 2;
		return (0);
	}
	return (1);
}

int check_if(char **s)
{
	int ret = 0;

	if (check_only_number(s) == 0)
		return (1);
	strcmp(s[2], ">") == 0 && strcmp(s[1], s[3]) > 0 ? ret = 1 : 0;
	strcmp(s[2], ">=") == 0 && strcmp(s[1], s[3]) >= 0 ? ret = 1 : 0;
	strcmp(s[2], "<") == 0 && strcmp(s[1], s[3]) < 0 ? ret = 1 : 0;
	strcmp(s[2], "<=") == 0 && strcmp(s[1], s[3]) <= 0 ? ret = 1 : 0;
	strcmp(s[2], "==") == 0 && strcmp(s[1], s[3]) == 0 ? ret = 1 : 0;
	strcmp(s[2], "!=") == 0 && strcmp(s[1], s[3]) != 0 ? ret = 1 : 0;
	ret_if = 4;
	return (ret);
}

int process_if(char **str, env_t *env)
{
	int ret_value = 0;

	if (check_if(str) != 1)
		return (0);
	my_exec(str + ret_if, env, (int[2]){0, 1});
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
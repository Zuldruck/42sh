/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int is_if_error(char **s)
{
	if (!s[2])
		return (0);
	if (strcmp(s[2], ">") == 0 || strcmp(s[2], ">=") == 0 ||
	strcmp(s[2], "<") == 0 || strcmp(s[2], "<=") == 0 ||
	strcmp(s[2], "==") == 0 || strcmp(s[2], "!=") == 0)
		if (!s[1] || !s[3])
			return (1);
	return (0);
}

int check_tab_len_if(char **s)
{
	if (!s[2])
		return (0);
	if (strcmp(s[2], ">") == 0 || strcmp(s[2], ">=") == 0 ||
	strcmp(s[2], "<") == 0 || strcmp(s[2], "<=") == 0 ||
	strcmp(s[2], "==") == 0 || strcmp(s[2], "!=") == 0)
		if (my_tablen(s) < 5)
			return (1);
	return (0);
}

int check_error_handling_if(char **str)
{
	if (my_tablen(str) < 3 || check_tab_len_if(str) != 0) {
		if (is_if_error(str) != 0) {
			printf("if: Expression Syntax.\n");
			return (1);
		}
		my_tablen(str) < 2 ?
		printf("if: Too few arguments.\n") : printf("if: Empty if.\n");
		return (1);
	}
	if (isdigit(str[1][0]) && isalpha(str[1][1])) {
		printf("if: Badly formed number.\n");
		return (1);
	}
	if (strlen(str[1]) == 1 && is_alpha_string(str[1]) &&
	is_if_error(str) != 0) {
		printf("if: Expression Syntax.\n");
		return (1);
	}
	return (0);
}

int check_only_number(char **s, int *ret_if)
{
	if (strcmp(s[2], ">") == 0 || strcmp(s[2], ">=") == 0 ||
	strcmp(s[2], "<") == 0 || strcmp(s[2], "<=") == 0
	|| strcmp(s[2], "==") == 0 || strcmp(s[2], "!=") == 0)
		return (1);
	if (is_alpha_string(s[1]) == 0) {
		*ret_if = 2;
		return (0);
	}
	return (1);
}
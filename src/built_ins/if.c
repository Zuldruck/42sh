/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int process_if(char **str, shell_t shell);

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

int process_if(char **str, shell_t shell)
{
	int ret_value = 0;
	int ret_if = 0;

	if (check_if(str, &ret_if) != 1) {
		if (check_then_if(str, shell) != 0)
			return (1);
		return (0);
	}
	if (check_then_if(str, shell) != 0)
		return (1);
	check_then(str) != 0 && str[ret_if] != NULL ?
	my_exec(str + ret_if, shell.env, (int[2]){0, 1}): 0;
	return (ret_value);
}

void clean_parenthesis(char **str)
{
	if (*str == NULL) {
		return;
	}
	for (int i = 0 ; (*str)[i] ; i++) {
		if ((*str)[i] == ')' || (*str)[i] == '(')
			(*str)[i] = ' ';
	}
	my_clean_str(*str);
}

int empty_string(char *str)
{
	for (int i = 0 ; str[i] ; i++) {
		if (str[i] != 32)
			return (1);
	}
	return (0);
}

void my_memmove(char **s1, char **s2)
{
	memset(*s1, 0, sizeof(char) * strlen(*s1));
	*s1 = strdup(*s2);
	memset(*s2, 0, sizeof(char) * strlen(*s2));
}

int need_to_memmove(char **str)
{
	if (!str)
		return (84);
	for (int i = 0 ; str[i] ; i++) {
		if (empty_string(str[i]) == 0)
			return (1);
	}
	return (0);
}

int pos_empty_case(char **str)
{
	int i = 0;

	while (empty_string(str[i]) == 1) {
			i++;
		}
	return (i);
}
int parse_if(char **str)
{
	int j = 0;

	if (!(str))
		return (84);
	for (int i = 0 ; (str)[i] ; i++) {
		if (is_parenthese((str)[i]) == 1) {
			clean_parenthesis(&str[i]);
		}
	}
	for (int i = 0 ; str[i] ; i++) {
		str[i] = my_clean_str(str[i]);
	}
	if (need_to_memmove(str) == 1) {
	for (int i = pos_empty_case(str) + 1 ; (str)[i] ; i++) {
		j = i;
		while (empty_string(str[i]) == 0) {
			i++;
		}
		my_memmove(&str[j - 1], &str[i]);
	}
	for (int i = 0 ; str[i] ; i++) {
		str[i] = my_clean_str(str[i]);
	}
	}
	for (int i = 0 ; str[i] ; i++) {
		if (empty_string(str[i]) == 0) {
			str[i] = NULL;
		}
	}
	return (0);
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
	if (parse_if(str) != 0) {
		*ret_value = 1;
		return;
	}
	if (process_if(str, shell) != 0) {
		*ret_value = 0;
		return;
	}
}
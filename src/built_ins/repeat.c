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
	for (int i = 0 ; str[i] ; i++) {
		if (isalpha(str[i]))
			return (1);
	}
	return (0);
}

int check_error_handling_repeat(char **str)
{
	if (my_tablen(str) < 3) {
		printf("repeat: Too few arguments.\n");
		return (1);
	}
	if (is_alpha_string(str[1]) == 1) {
		printf("repeat: Badly formed number.\n");
		return (1);
	}
	return (0);
}

char **add_special_tab(char **tab, int user_choice)
{
	char **tmp = calloc(0, sizeof(char *) * (my_tablen(tab) + 1));
	int j = 0;

	for (int i = user_choice ; tab[i] ; i++)
		tmp[j++] = strdup(tab[i]);
	tmp[j] = NULL;
	return (tmp);
}

int process_repeat(char **str, env_t *env)
{
	char **tmp_tab = NULL;
	int user_loop = atoi(str[1]);
	int ret_value_cmd = 0;

	tmp_tab = add_special_tab(str, 2);
	for (int i = 0 ; i != user_loop ; i++) {
		parse_cmd(env, convert_tab_to_string(tmp_tab), &ret_value_cmd);
	}
	my_free_tab(tmp_tab);
	return (ret_value_cmd);
}

void repeat_func(char **str, env_t *env, int *ret_value)
{
	if (!str || !env) {
		*ret_value = 1;
		return;
	}
	if (check_error_handling_repeat(str) != 0) {
		*ret_value = 1;
		return;
	}
	if (str[0] && str[1] && process_repeat(str, env) != 0) {
		*ret_value = 1;
		return;
	}
}

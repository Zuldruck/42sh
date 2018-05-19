/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int check_error_handling_foreach(char **str)
{
	if (is_alpha_string(str[1]) != 1) {
		printf("foreach: Variable name must begin with a letter.\n");
		return (1);
	}
	return (0);
}

char *process_foreach(void)
{
	char *s = NULL;
	char *string = NULL;

	isatty(0) ? write(1, "foreach? ", 9) : 0;
	while ((s = get_next_line(stdin))) {
		if (!my_strcmp("end", s))
			break;
		else
			string = my_strcat(string ? string : "",
			my_strcat(";", s));
		isatty(0) ? write(1, "foreach? ", 9) : 0;
		free(s);
	}
	free(s);
	return (string);
}

void print_tab(char **tab)
{
	if (!tab)
		return;
	for (int i = 0 ; tab[i] ; i++) {
		printf("%s\n", tab[i]);
	}
}

void foreach_func(char **str, env_t *env, int *ret_value)
{
	char *ret = NULL;
//	int loop_foreach = 0;

	if (!str || !env) {
		*ret_value = 1;
		return;
	}
	if (check_error_handling_foreach(str) != 0) {
		*ret_value = 1;
		return;
	}
	if ((ret = process_foreach()) == NULL) {
		*ret_value = 1;
		return;
	}
//	loop_foreach = my_tablen(str) - 2;
	parse_cmd(env, ret, ret_value);
}

/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int check_then(char **s)
{
	if (!s || !s[4])
		return (1);
	if (strcmp(s[4], "then") == 0)
		return (0);
	return (1);
}

int process_then(char *str, env_t *env)
{
	char **tmp = NULL;

	if (str && strncmp(str, "else if",7) == 0) {
		tmp = my_str_to_word_array(str + 4, 32);
		if (check_error_handling_if(tmp) != 0) {
			free (tmp);
			return (1);
		}
		process_if(tmp, env);
		free (tmp);
		return (1);
	}
	return (0);
}

int check_then_if(char **s, env_t *env)
{
	char *input = NULL;

	(void) env;
	if (check_then(s) != 0)
		return (0);
	isatty(0) ? write (1, "if? ", 4) : 0;
	if ((input = get_next_line(stdin)) == NULL)
		return (1);
	while (input != NULL && ((my_strcmp(input, "endif") != 0) &&
	(my_strcmp(input, "else") != 0))) {
		if (process_then(input, env) != 0)
			break;
		isatty(0) ? write (1, "if? ", 4) : 0;
		if ((input = get_next_line(stdin)) == NULL)
			return (1);
	}
	return (0);
}

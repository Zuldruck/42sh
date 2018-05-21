/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parse_quotes
*/

#include "42sh.h"

int check_quotes(char *cmd, int i)
{
	int offset = 0;
	int save = i;
	char c = 0;

	if (cmd[i] != '"' && cmd[i] != '\'')
		return (i);
	c = cmd[i];
	for (i--; i >= 0; i--) {
		offset++;
		if (cmd[i] == c)
			return (save - offset);
	}
	printf("Unmatched %c.\n", c);
	return (-1);
}

int str_contain_quotes(char *cmd)
{
	for (int i = 0; cmd[i]; i++)
		if (cmd[i] == '"' || cmd[i] == '\'')
			return (1);
	return (0);
}

char *get_next_arg(char **cmd)
{
	int size = 0;
	int word = 0;
	char *arg = NULL;

	if (!str_contain_quotes(cmd[word]))
		return (cmd[word]);
	for (int i = 0; cmd[word][i]; i++) {
		arg = realloc(arg, size + 1);
		arg[size] = cmd[word][i];
		size += 1;
	}
	return (arg);
}

void parse_quotes(char **cmd)
{
	char *str = NULL;
	char **cmd = malloc(sizeof(char *));

	while ((str = get_next_arg(cmd))) {
		if (!str_contain_char(cmd[0]))
			cmd += 1;
		printf("%s\n", str);
	}
}
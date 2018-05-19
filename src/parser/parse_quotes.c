/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parse_quotes
*/

#include "42sh.h"

int check_quotes_for_separators(char *cmd, int i)
{
	int offset = 0;
	int save = i;
	char c = 0;

	if (cmd[i] != '"' && cmd[i] != '\'')
		return (i);
	c = cmd[i];
	for (i++; cmd[i]; i++) {
		offset++;
		if (cmd[i] == c)
			return (save + offset);
	}
	printf("Unmatched %c.\n", c);
	return (-1);
}

int check_quotes_for_pipes_and_redirect(char *cmd, int i)
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

// void parse_quotes(char **cmd)
// {
// 	for (int i = 0; cmd[i]; i++) {

// 	}
// }
/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int check_wildcard(char *cmd)
{
	if (!cmd)
		return (84);
	for (int i = 0 ; cmd[i] ; i++)
		if (cmd[i] == '*')
			return (1);
	return (0);
}

char *parse_wildcard(char *cmd, int clean)
{
	char **tab_cmd = NULL;
	char *ret = NULL;
	static int pos_tab = 0;

	if (!cmd || clean == 1) {
		if (!cmd)
			exit (84);
		pos_tab = 0;
		return (NULL);
	}
	tab_cmd = my_str_to_word_array(cmd, 32);
	for (int i = clean == 2 ? 0 : pos_tab ; tab_cmd[i] ; i++) {
		if (check_wildcard(tab_cmd[i]) == 1) {
			pos_tab = i + 1;
			ret = strdup(tab_cmd[i]);
			my_free_tab(tab_cmd);
			return (ret);
		}
	}
	my_free_tab(tab_cmd);
	return (NULL);
}

int count_wild(char *cmd)
{
	char **tab_cmd = NULL;
	int wildcard = 0;

	if (!cmd)
		exit (84);
	tab_cmd = my_str_to_word_array(cmd, 32);
	for (int i = 0 ; tab_cmd[i] ; i++)
		if (check_wildcard(tab_cmd[i]) == 1)
			wildcard++;
	my_free_tab(tab_cmd);
	return (wildcard);
}
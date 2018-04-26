/*
** EPITECH PROJECT, 2018
** minishell1_2017
** File description:
** minishell1_2017 made by Sanchez Lucas
*/

#include "42sh.h"

int test_concat_exec(char *test_access, char **path, char **str)
{
	if (access(test_access, X_OK) == 0) {
		str[0] = my_strdup(test_access);
		my_free_tab(path);
		free(test_access);
		return (1);
	}
	return (0);
}

int concat_exec(char **str, env_t *env)
{
	char **path = my_str_to_word_array(get_env(env, "PATH"), ':');
	char *test_access = NULL;
	char *concat = NULL;
	int i = 0;

	if (!path || !str || !str[0])
		return (0);
	while (path[i] != NULL) {
		concat = my_strcat("/", str[0]);
		test_access = my_strcat(path[i], concat);
		free(concat);
		if (test_concat_exec(test_access, path, str) == 1)
			return (1);
		i++;
		free(test_access);
	}
	my_free_tab(path);
	return (0);
}

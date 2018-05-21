/*
** EPITECH PROJECT, 2018
** PSU_minishell1_2017
** File description:
** PSU_minishell1_2017 made by Sanchez Lucas
*/

#include "42sh.h"

int main(int ac, char **av, char **envp)
{
	env_t *my_env = NULL;
	int ret = 0;

	(void) av;
	if (ac != 1)
		return (84);
	if (verif_env(envp) == 0)
		my_env = fill_my_env(my_env);
	else
		my_env = create_list(envp);
	my_loop(my_env, ret);
	return (0);
}

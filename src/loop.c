/*
** EPITECH PROJECT, 2018
** minishell1_2017
** File description:
** minishell1_2017 made by Sanchez Lucas
*/

#include "42sh.h"

void my_signals(void)
{
	signal(SIGINT, sig_handler);
	//signal(SIGSEGV, sig_handler);
	signal(SIGPIPE, sig_handler);
}

void my_loop(env_t *env, int ret_value)
{
	char *str = NULL;

	global_env = env;
	while (1) {
		my_signals();
		print_prompt(env);
		str = get_next_line(STDIN_FILENO);
		if (str == NULL) {
			(isatty(STDIN_FILENO) ? my_printf("exit\n") : 0);
			free_list(env);
			exit(ret_value);
		} else if (!str[0]) {
			free(str);
			continue;
		}
		ret_value = 0;
		parse_cmd(env, str, &ret_value);
	}
}

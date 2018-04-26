/*
** EPITECH PROJECT, 2018
** minishell1_2017
** File description:
** minishell1_2017 made by Sanchez Lucas
*/

#include "42sh.h"

void reset_fd(int *fd, int *save)
{
	close(fd[0]);
	close(fd[1]);
	dup2(save[0], 0);
	dup2(save[1], 1);
}

int is_a_env_value(env_t *env, char *str)
{
	if (get_env(env, str + 1) == NULL)
		return (0);
	return (1);
}


int check_undefined_variable(char **str, env_t *env)
{
	for (int i = 1 ; str[i] ; i++)
		if (str[i][0] == '$' && is_a_env_value(env, str[i]) == 0) {
			my_printf("%s: Undefined variable.\n", str[i] + 1);
			return (1);
		}
	return (0);
}

void process_args_echo(char **str, env_t *env)
{
	for (int i = 1 ; str[i] ; i++) {
		if (str[i][0] == '$') {
			my_printf("%s", get_env(env, str[i] + 1));
			str[i + 1] != NULL ? write(1, " ", 1) : 0;
		}
		else if (str[i] != NULL) {
			my_printf("%s", str[i]);
			str[i + 1] != NULL ? write(1, " ", 1) : 0;
		}
	}
}

void echo_func(char **str, env_t *env, int *ret_value)
{
	if (!str) {
		*ret_value = 84;
		return;
	}
	if (str && !str[1]) {
		my_printf("\n");
		*ret_value = 0;
		return;
	}
	if (check_undefined_variable(str, env) != 0) {
		*ret_value = 1;
		return;
	}
	process_args_echo(str, env);
	write(1, "\n", 1);
}

int check_built_ins(char **str, env_t *env, int *ret_value, int *fd)
{
	int i = 0;
	char *built_ins[] = {"cd", "exit", "env", "setenv", "unsetenv",
	"echo", NULL};
	void (*fptr[])(char **, env_t *, int *) = {&cd_func, &exit_func,
	&env_func, &setenv_func, &unsetenv_func, &echo_func};
	int save[2];

	save[0] = dup(0);
	save[1] = dup(1);
	while (built_ins[i]) {
		if (str && my_strcmp(str[0], built_ins[i]) == 0) {
			dup2(fd[0], 0);
			dup2(fd[1], 1);
			fptr[i](str, env, ret_value);
			reset_fd(fd, save);
			return (0);
		}
		i++;
	}
	return (1);
}

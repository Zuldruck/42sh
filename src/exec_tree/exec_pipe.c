/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** exec_pipe
*/

#include "42sh.h"

void exec_pipe(btree_t *pipe, env_t *env, int *ret_value)
{
	pid_t pid = 0;

	set_pipefd(pipe);
	pid = fork();
	if (!pid) {
		exec_tree(pipe->left, env, ret_value);
		close(pipe->left->fd[1]);
		exit(0);
	}
	close(pipe->left->fd[1]);
	exec_tree(pipe->right, env, ret_value);
	waitpid(pid, NULL, 0);
}
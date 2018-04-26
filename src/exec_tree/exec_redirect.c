/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** exec_redirect
*/

#include "42sh.h"

int redirect_error_handling(int fd, char **tab, env_t *env, int *ret_value)
{
	if (!tab || !tab[0])
		return (0);
	if (!concat_exec(tab, env) && access(tab[0], X_OK) == -1) {
		my_printf("%s: Command not found.\n", tab[0]);
		close(fd);
		my_free_tab(tab);
		*ret_value = 1;
		return (1);
	}
	return (0);
}

void exec_right_redirect(btree_t *redirect, env_t *env, int *ret_value)
{
	char **tab = my_str_to_word_array(redirect->left->cmd, ' ');
	int fd = open(redirect->right->cmd,
					O_WRONLY | O_TRUNC | O_CREAT, 00664);

	redirect->left->fd[1] = fd;
	if (redirect_error_handling(fd, tab, env, ret_value))
		return;
	my_free_tab(tab);
	exec_tree(redirect->left, env, ret_value);
	close(fd);
}

void exec_double_right_redirect(btree_t *redirect, env_t *env, int *ret_value)
{
	char **tab = my_str_to_word_array(redirect->left->cmd, ' ');
	int fd = open(redirect->right->cmd,
					O_WRONLY | O_CREAT | O_APPEND, 00664);

	redirect->left->fd[1] = fd;
	if (redirect_error_handling(fd, tab, env, ret_value))
		return;
	my_free_tab(tab);
	exec_tree(redirect->left, env, ret_value);
	close(fd);
}

void exec_left_redirect(btree_t *redirect, env_t *env, int *ret_value)
{
	char **tab = my_str_to_word_array(redirect->left->cmd, ' ');
	int fd = open(redirect->right->cmd, O_RDONLY);

	if (fd == -1) {
		my_printf("%s: No such file or directory.\n",
							redirect->right->cmd);
		my_free_tab(tab);
		*ret_value = 1;
		return;
	}
	redirect->left->fd[0] = fd;
	if (redirect_error_handling(fd, tab, env, ret_value))
		return;
	my_free_tab(tab);
	exec_tree(redirect->left, env, ret_value);
	close(fd);
}
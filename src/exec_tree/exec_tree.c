/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** exec_tree
*/

#include "42sh.h"

// int check_environment_variables(char **str, env_t *env, int *ret_value, int *fd)
// {
// 	int save[2];

// 	if (!str || !env) {
// 		*ret_value = 84;
// 		return (1);
// 	}
// 	save[0] = dup(0);
// 	save[1] = dup(1);
// 	if (str && str[0] && str[0][0] == '$') {
// 		dup2(fd[0], 0);
// 		dup2(fd[1], 1);
// 		my_printf("%s", get_env(env, str[0] + 1));
// 		exec_error_handling_env_variables(str, env);
// 		return (0);
// 	}
// 	return (1);
// }

void exec_tree(btree_t *tree, env_t *env, int *ret_value)
{
	char **word_tab = NULL;
	operator_t op_tab[] = {{";", &exec_semicolon},
	{"|", &exec_pipe}, {">", &exec_right_redirect},
	{"<", &exec_left_redirect}, {">>", &exec_double_right_redirect},
	{"<<", &exec_double_left_redirect}, {"&&", &exec_double_and},
	{"||", &exec_double_or}, {NULL, NULL}};

	for (int i = 0; tree->op && op_tab[i].fptr; i++) {
		if (!my_strcmp(tree->op, op_tab[i].op)) {
			op_tab[i].fptr(tree, env, ret_value);
			return;
		}
	}
	word_tab = my_str_to_word_array(tree->cmd, ' ');
	if (check_built_ins(word_tab, env, ret_value, tree->fd) == 1)
		if (word_tab && word_tab[0] && word_tab[0][0])
			*ret_value = my_exec(word_tab, env, tree->fd);
	my_free_tab(word_tab);
}
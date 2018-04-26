/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parsing_cmd
*/

#include "42sh.h"

int check_semicolon(btree_t *node, char *cmd, int i)
{
	if (cmd[i] == ';') {
		cmd[i] = 0;
		node->right = create_btree_node( \
				my_clean_str(node->cmd + i + 1), NULL);
		node->left = create_btree_node(my_clean_str(cmd), NULL);
		node->cmd = NULL;
		node->op = my_strdup(";");
		parse_cmd_for_separator(node->left);
		parse_cmd_for_separator(node->right);
		return (1);
	}
	return (0);
}

int check_double_and_double_or(btree_t *node, char *cmd, int i)
{
	if ((cmd[i] == '&' && cmd[i - 1] == '&')
	|| (cmd[i] == '|' && cmd[i - 1] == '|')) {
		if (cmd[i] == '&')
			node->op = my_strdup("&&");
		else
			node->op = my_strdup("||");
		cmd[i] = 0;
		cmd[i - 1] = 0;
		node->right = create_btree_node( \
				my_clean_str(node->cmd + i + 1), NULL);
		node->left = create_btree_node(my_clean_str(cmd), NULL);
		node->cmd = NULL;
		parse_cmd_for_separator(node->left);
		parse_cmd_for_separator(node->right);
		return (1);
	}
	return (0);
}

void parse_cmd_for_separator(btree_t *node)
{
	char *cmd = my_strdup(node->cmd);
	int len = my_strlen(node->cmd);

	for (int i = len - 1; i > 0; i--) {
		if (check_semicolon(node, cmd, i))
			break;
		if (check_double_and_double_or(node, cmd, i))
			break;
	}
	free(cmd);
}

void free_tree(btree_t *tree)
{
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free_btree_node(tree);
	free(tree);
}

void parse_cmd(env_t *env, char *cmd, int *ret_value)
{
	btree_t *node = create_btree_node(my_clean_str(cmd), NULL);

	free(cmd);
	parse_cmd_for_separator(node);
	parse_cmd_for_pipes_and_redirections(node);
	if (btree_error_handling(node, 0)) {
		free_tree(node);
		return;
	}
	exec_tree(node, env, ret_value);
	free_tree(node);
}
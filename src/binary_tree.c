/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** binary_tree
*/

#include "42sh.h"

void free_btree_node(btree_t *node)
{
	if (node->op)
		free(node->op);
	if (node->cmd)
		free(node->cmd);
}

btree_t *create_btree_node(char *cmd, char *op)
{
	btree_t *node = malloc(sizeof(*node));

	node->cmd = cmd ? cmd : NULL;
	node->op = op ? op : NULL;
	node->fd[0] = 0;
	node->fd[1] = 1;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void display_btree(btree_t *tree)
{
	if (tree->op)
		my_printf("op = %s\n", tree->op);
	if (tree->cmd)
		my_printf("cmd = %s\n", tree->cmd);
	my_printf("fd[0] = %d\nfd[1] = %d\n", tree->fd[0], tree->fd[1]);
	if (tree->left) {
		my_printf("LEFT =\n");
		display_btree(tree->left);
	}
	if (tree->right) {
		my_printf("RIGHT =\n");
		display_btree(tree->right);
	}
}
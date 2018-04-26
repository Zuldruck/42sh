/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** exec_semicolon
*/

#include "42sh.h"

void exec_semicolon(btree_t *semicolon, env_t *env, int *ret_value)
{
	exec_tree(semicolon->left, env, ret_value);
	exec_tree(semicolon->right, env, ret_value);
}

void exec_double_and(btree_t *semicolon, env_t *env, int *ret_value)
{
	exec_tree(semicolon->left, env, ret_value);
	if (*ret_value != 0)
		return;
	exec_tree(semicolon->right, env, ret_value);
}

void exec_double_or(btree_t *semicolon, env_t *env, int *ret_value)
{
	exec_tree(semicolon->left, env, ret_value);
	if (*ret_value == 0)
		return;
	exec_tree(semicolon->right, env, ret_value);
}
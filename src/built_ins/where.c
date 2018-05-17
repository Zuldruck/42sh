/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** where
*/

#include "42sh.h"

void where_func(char **str, env_t *env, int *ret_value)
{
	if (my_tablen(str) < 2) {
		*ret_value = 1;
		printf("where: Too few arguments.\n");
		return;
	}
	for (int i = 1; str[i]; i++) {
		
	}
}
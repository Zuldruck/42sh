/*
** EPITECH PROJECT, 2017
** PSU_42sh_2017
** File description:
** create_lvar.c
*/

#include "my.h"
#include "42sh.h"

ll_lvar_t *init_lvar(void)
{
	ll_lvar_t *varl = malloc(sizeof(*varl));

	varl->name = NULL;
	varl->value = NULL;
	varl->next = NULL;
	return (varl);
}

char *get_lvar_one(char *str)
{
	char *one = malloc(sizeof(char) * strlen(str) + 1);
	int i = 0;

	while (str[i] != '=' && str[i]) {
		one[i] = str[i];
		i++;
	}
	one[i] = 0;
	return (one);
}

char *get_lvar_two(char *str)
{
	char *two = malloc(sizeof(char) * strlen(str) + 1);
	int i = 0;
	int a = 0;

	while (str[i] != '=' && str[i])
		i++;
	i++;
	while (str[i]) {
		two[a] = str[i];
		i++;
		a++;
	}
	two[a] = 0;
	return (two);
}

int valid_lvar(char *str)
{
	char **str_tab = NULL;
	int equal = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] == '=')
			equal = 1;
	}
	if (equal == 0)
		return (0);
	str_tab = my_str_to_word_array(str, '=');
	(void)str_tab;
	return (1);
}

int is_sorted_lvar(ll_lvar_t *lvar)
{
	ll_lvar_t *tmp = lvar->next;

	if (tmp == NULL)
		return (1);
	while (tmp->next) {
		if (strcmp(tmp->name, tmp->next->name) > 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void swap_elem_lvar(ll_lvar_t *lvar1, ll_lvar_t *lvar2)
{
	char *sname = NULL;
	char *svalue = NULL;

	sname = lvar1->name;
	svalue = lvar1->value;
	lvar1->name = lvar2->name;
	lvar1->value = lvar2->value;
	lvar2->name = sname;
	lvar2->value = svalue;
}

void sort_lvar(ll_lvar_t *lvar)
{
	ll_lvar_t *tmp = NULL;

	while (is_sorted_lvar(lvar) == 0) {
		tmp = lvar->next;
		while (tmp->next) {
			if (strcmp(tmp->name, tmp->next->name) > 0)
				swap_elem_lvar(tmp, tmp->next);
			tmp = tmp->next;
		}
	}
}

void print_lvar(ll_lvar_t *lvar)
{
	sort_lvar(lvar);
	for (ll_lvar_t *tmp = lvar->next; tmp; tmp = tmp->next) {
		printf("%s\t%s\n", tmp->name, tmp->value);
	}
}

void set_func(char **str, env_t *env, int *ret_value)
{
	int ret = 0;

	if (my_tablen(str) == 2) {
		ret = valid_lvar(str[1]);
		if (ret == 1) {
			create_lvar(get_lvar_one(str[1]),
			get_lvar_two(str[1]), lvar);
		}
	} else if (my_tablen(str) == 1) {
		print_lvar(lvar);
	}
	(void)env;
	(void)ret_value;
}

int replace_lvar(char *name, char *value, ll_lvar_t *lvar)
{
	for (ll_lvar_t *tmp = lvar->next; tmp; tmp = tmp->next) {
		if (strcmp(tmp->name, name) == 0) {
			free(tmp->value);
			tmp->value = malloc(sizeof(char) * strlen(value) + 1);
			strcpy(tmp->value, value);
			return (1);
		}
	}
	return (0);
}

void create_lvar(char *name, char *value, ll_lvar_t *lvar)
{
	ll_lvar_t *n = malloc(sizeof(*n));
	ll_lvar_t *tmp = lvar;

	if (replace_lvar(name, value, lvar) == 1)
		return;
	n->next = NULL;
	n->name = malloc(sizeof(char) * strlen(name) + 1);
	n->value = malloc(sizeof(char) * strlen(value) + 1);
	strcpy(n->name, name);
	strcpy(n->value, value);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = n;
}
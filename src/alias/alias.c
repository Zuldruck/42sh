/*
** EPITECH PROJECT, 2017
** alias42sh
** File description:
** alias.c
*/

#include "42sh.h"
#include "my.h"

char 		*get_file(char *path)
{
	int ret = 0;
	char *file = NULL;
	struct stat sb;
	int fd = open(path, O_RDONLY);

	if (fd == -1)
		return (NULL);
	stat(path, &sb);
	file = malloc(sizeof(char) * (long long int)sb.st_size + 1);
	ret = read(fd, file, sb.st_size);
	if (ret == -1)
		return (NULL);
	file[ret] = 0;
	return (file);
}

void		synchro_with_file(ll_alias_t *n)
{
	(void)n;
	if (access(PATH_42SH, F_OK) == 0)
		printf("ouiiii\n");
}

int		check_name_exist(ll_alias_t *lla, char *name, char *alias)
{
	for (ll_alias_t *tmp = lla->next; tmp; tmp = tmp->next) {
		if (strcmp(tmp->name, name) == 0) {
			free(tmp->alias);
			tmp->alias = malloc(sizeof(char) * strlen(alias) + 1);
			strcpy(tmp->alias, alias);
			return (1);
		}
	}
	return (0);
}

void		add_alias(char *name, char *alias, ll_alias_t *lla, int par)
{
	ll_alias_t *n;
	ll_alias_t *tmp = lla;

	if (check_name_exist(lla, name, alias) == 1) {
		synchro_with_file(lla);
		return;
	}
	n = malloc(sizeof(*n));
	n->par = par;
	n->name = malloc(sizeof(char) * strlen(name) + 1);
	n->alias = malloc(sizeof(char) * strlen(alias) + 1);
	strcpy(n->name, name);
	strcpy(n->alias, alias);
	n->next = NULL;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = n;
	synchro_with_file(lla);
}

void		print_alias(ll_alias_t *n)
{
	for (ll_alias_t *tmp = n->next; tmp; tmp = tmp->next) {
		if (tmp->par == 0)
			printf("%s\t%s\n", tmp->name, tmp->alias);
		else
			printf("%s\t(%s)\n", tmp->name, tmp->alias);
	}

}

ll_alias_t 	*init_lla(void)
{
	ll_alias_t *n = malloc(sizeof(*n));

	n->name = NULL;
	n->alias = NULL;
	n->next = NULL;
	synchro_with_file(n);
	return (n);
}

int		is_sorted(ll_alias_t *lla)
{
	ll_alias_t *tmp = lla->next;

	if (tmp == NULL)
		return (1);
	while (tmp->next) {
		if (strcmp(tmp->name, tmp->next->name) > 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void		swap_elem(ll_alias_t *tmp1, ll_alias_t *tmp2)
{
	char *sname = NULL;
	char *salias = NULL;
	int spar;

	sname = tmp1->name;
	salias = tmp1->alias;
	spar = tmp1->par;
	tmp1->name = tmp2->name;
	tmp1->alias = tmp2->alias;
	tmp1->par = tmp2->par;
	tmp2->name = sname;
	tmp2->alias = salias;
	tmp2->par = spar;
}

void		sort_lla(ll_alias_t *lla)
{
	ll_alias_t *tmp = NULL;

	while (is_sorted(lla) == 0) {
		tmp = lla->next;
		while (tmp->next) {
			if (strcmp(tmp->name, tmp->next->name) > 0) {
				swap_elem(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
	}
}

void 		my_free_lla(ll_alias_t*lla)
{
	ll_alias_t *tmp = NULL;

	while (lla) {
		tmp = lla;
		lla = lla->next;
		if (tmp && tmp->name)
			free(tmp->name);
		if (tmp && tmp->alias)
			free(tmp->alias);
		free(tmp);
	}
}

char 		*get_str_alias(char **str)
{
	int i = 2;
	char *str_alias = NULL;

	while (str[i]) {
		str_alias = my_strcat(str_alias, str[i]);
		if (str[i+1])
			str_alias = my_strcat(str_alias, " ");
		i++;
	}
	return (str_alias);
}

void 		alias_func(char **str, env_t *env, int *ret_value)
{
	char *str_alias = NULL;

	(void)env;
	(void)ret_value;
	if (my_tablen(str) > 3) {
		str_alias = get_str_alias(str);
		add_alias(str[1], str_alias, lla, 1);
	} else if (my_tablen(str) == 3) {
		add_alias(str[1], str[2], lla, 0);
	} else if (my_tablen(str) == 1) {
		sort_lla(lla);
		print_alias(lla);
	}

}

char		**my_strtab_cat(char **cmd, char **str)
{
	char **nstr = malloc(sizeof(char *) * my_tablen(str));
	int i = 0;
	int b = 1;

	if (my_tablen(str) == 1)
		return (cmd);
	while (i < my_tablen(cmd)) {
		strcpy(nstr[i], cmd[i]);
		i++;
	}
	while (b < my_tablen(str))
		strcpy(nstr[i++], str[b++]);
	return (nstr);
}

char		**replace_alias(char **str, ll_alias_t *lla)
{
	ll_alias_t *tmp = lla->next;
	char **cmd = NULL;

	for (; tmp; tmp = tmp->next) {
		if (strcmp(str[0], tmp->name) == 0 && tmp->name) {
			cmd = my_str_to_word_array(tmp->alias, ' ');
			cmd = my_strtab_cat(cmd, str);
			return (cmd);
		}
	}
	return (str);
}
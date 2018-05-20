/*
** EPITECH PROJECT, 2017
** PSU_42sh_2017
** File description:
** create_alias.c
*/

#include "my.h"
#include "42sh.h"

void write_alias(ll_alias_t *lla)
{
	FILE *file = fopen(PATH_42SH, "w");

	sort_lla(lla);
	for (ll_alias_t *tmp = lla->next; tmp; tmp = tmp->next) {
		fprintf(file, "%s\t%s\n", tmp->name, tmp->alias);
	}
	fclose(file);
}

void		add_alias(char *name, char *alias, ll_alias_t *lla, int par)
{
	ll_alias_t *n;
	ll_alias_t *tmp = lla;

	if (check_name_exist(lla, name, alias) == 1)
		return;
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
	write_alias(lla);
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

void		synchro_with_file(ll_alias_t *lla)
{
	char **file_dd = NULL;
	char *file = NULL;
	FILE *fd = NULL;

	if (access(PATH_42SH, F_OK) == 0) {
		file = get_file(PATH_42SH);
		if (file == NULL) {
			fd = fopen(PATH_42SH, "w+");
			fclose(fd);
			return;
		}
		file_dd = my_str_to_word_array(file, '\n');
		for (int i = 0; file_dd[i]; i++)
			add_alias(get_name(file_dd[i]), get_alias(file_dd[i]), \
			lla, 0);
	} else {
		fd = fopen(PATH_42SH, "w+");
		fclose(fd);
	}
}
/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "42sh.h"

int check_whereis_ref(char **tab , char *ref)
{
	for (int i = 0 ; tab[i] ; i++)
		if (strcmp(tab[i], ref) == 0)
			return (i);
	return (0);
}

void add_new_value_from_wildcard(char **tab, char **cmd, char *ref)
{
	char **tab_tmp = my_str_to_word_array(*cmd, ' ');
	char *ret_convert = NULL;
	int pos_ref = check_whereis_ref(tab_tmp, ref);

	ret_convert = convert_tab_to_string(tab);
	tab_tmp[pos_ref] = strdup(ret_convert);
	*cmd = convert_tab_to_string(tab_tmp);
	free (ret_convert);
	my_free_tab(tab_tmp);
}

void loop_wildcard(char **cmd, int retval, glob_t *paths, int *check_error)
{
	int count_wildcard = count_wild(*cmd);
	int total_wildcard = count_wildcard;
	char *ref = NULL;

	if (retval == 0) {
		ref = parse_wildcard(*cmd, 2);
		add_new_value_from_wildcard(paths->gl_pathv, cmd,
		ref);
		free (ref);
		globfree(paths);
	} else {
		ref = parse_wildcard(*cmd, 2);
		total_wildcard == 1 ? printf("%s: No match.\n",
		ref) : 0;
		free (ref);
		*check_error = 1;
	}
}

void body_wildcard(glob_t *paths, char **cmd, int *check_error)
{
	char *parse_star = NULL;
	int count_wildcard = count_wild(*cmd);
	int retval = 0;

	while (count_wildcard != 0) {
		parse_star = parse_wildcard(*cmd, 0);
		retval = glob(parse_star, GLOB_NOCHECK && GLOB_NOSORT
		&& GLOB_NOMATCH, NULL, paths);
		loop_wildcard(cmd, retval, paths, check_error);
		count_wildcard--;
		free (parse_star);
	}
	parse_wildcard(*cmd, 1);
}

int process_wildcard(char **cmd)
{
	glob_t paths;
	int check_error = 0;

	if (!cmd)
		return (0);
	paths.gl_pathc = 0;
	paths.gl_pathv = NULL;
	paths.gl_offs = 0;
	body_wildcard(&paths, cmd, &check_error);
	if (check_error != 0) {
		check_error = 0;
		return (1);
	}
	return (0);
}
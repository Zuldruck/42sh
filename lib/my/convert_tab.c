/*
** EPITECH PROJECT, 2018
** null
** File description:
** null
*/

#include "../../include/my.h"

char *convert_tab_to_string(char **tab)
{
	char *result = NULL;
	char *tmp = NULL;
	char *tmp_result = NULL;

	for (int i = 0 ; tab[i] ; i++) {
		tmp = my_strcat(" ", tab[i]);
		if (result) {
			tmp_result = strdup(result);
			free (result);
			result = my_strcat(tmp_result, tmp);
			free (tmp_result);
		} else
			result = strdup(tmp);
		free (tmp);
	}
	return (result);
}
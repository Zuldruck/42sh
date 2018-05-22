/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parse_quotes
*/

#include "42sh.h"

int check_quotes(char *cmd, int i)
{
	int offset = 0;
	int save = i;
	char c = 0;

	if (cmd[i] != '"' && cmd[i] != '\'')
		return (i);
	c = cmd[i];
	for (i--; i >= 0; i--) {
		offset++;
		if (cmd[i] == c)
			return (save - offset);
	}
	printf("Unmatched %c.\n", c);
	return (-1);
}

char *get_next_arg(char ***cmd, char *arg, int *size, char *quote_char)
{
	if (!(*cmd)[0])
		return (NULL);
	printf("cmd[0] = %s\n", (*cmd)[0]);
	for (int i = 0; (*cmd[0]) && (*cmd[0])[i]; i++) {
		if ((*cmd[0])[i] == '"' || (*cmd[0])[i] == '\'') {
			*quote_char = (*quote_char == 0 ? (*cmd[0])[i] : 0);
			continue;
		}
		arg = realloc(arg, *size);
		arg[*size - 1] = (*cmd[0])[i];
		*size += 1;
	}
	*cmd += 1;
	if ((*cmd)[0] && *quote_char) {
		arg = realloc(arg, *size);
		arg[*size - 1] = ' ';
		*size += 1;
		arg = get_next_arg(cmd, arg, size, quote_char);
	}
	arg = realloc(arg, *size);
	arg[*size - 1] = 0;
	return (arg);
}

void parse_quotes(char **cmd)
{
	char *str = NULL;
	int size = 1;
	char quote_char = 0;

	while ((str = get_next_arg(&cmd, NULL, &size, &quote_char))) {
		printf("%s\n", str);
		free(str);
		str = NULL;
	}
}

// int main(int ac, char **av)
// {

// 	parse_quotes(av + 1);
// 	return (0);
// }
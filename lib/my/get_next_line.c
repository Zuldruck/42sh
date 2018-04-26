/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2017
** File description:
** CPE_getnextline_2017 made by Sanchez Lucas
*/

#include <stdlib.h>
#include <unistd.h>

char *my_strcat_gnl(const char *dest, const char *src)
{
	int i = 0;
	int len_d = 0;
	int len_s = 0;
	char *str;

	while (dest && dest[len_d] != 0 && dest[len_d] != '\n')
		len_d++;
	while (src && src[len_s] != 0 && src[len_s] != '\n')
		len_s++;
	str = malloc(sizeof(char) * (len_d + len_s + 1));
	if (str == NULL)
		return (NULL);
	for (i = 0; dest && dest[i] != 0 && dest[i] != '\n'; i++)
		str[i] = dest[i];
	for (int j = 0; src && src[j] != 0 && src[j] != '\n'; j++) {
		str[i] = src[j];
		i++;
	}
	str[i] = 0;
	return (str);
}

int check_endline(const char *str, int a)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (i < 1) {
		if (str != NULL && str[i] == 0 && a == 0)
			return (i);
		else if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char *my_calloc(char *str, int size)
{
	int i = 0;

	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	while (i < size + 1) {
		str[i] = 0;
		i++;
	}
	return (str);
}

char *loop_until_endline(int fd, char *buffer, char *result, int *endline)
{
	int a = 0;
	int len = 0;

	while ((a = read(fd, buffer, 1)) > 0) {
		buffer[a] = 0;
		result = my_strcat_gnl(result, buffer);
		*endline = check_endline(buffer, 0);
		if (*endline > 0)
			return (result);
	}
	buffer[a] = 0;
	for (len = 0; result && result[len]; len++);
	if (len > 0)
		return (result);
	free(buffer);
	if (result)
		free(result);
	return (NULL);
}

char *get_next_line(int fd)
{
	static char *buffer = NULL;
	int endline = 0;
	char *result = NULL;

	endline = check_endline(buffer, 1);
	if (endline > 0) {
		for (result = my_calloc(result, endline - 1); !result;)
			return (NULL);
		for (int i = 0; buffer[i] != '\n' && buffer[i] != 0; i++)
			result[i] = buffer[i];
		result[endline - 1] = 0;
		buffer += endline;
		return (result);
	}
	result = (buffer != NULL ? my_strcat_gnl(result, buffer) : 0);
	for (buffer = my_calloc(buffer, 1); !buffer;)
		return (NULL);
	result = loop_until_endline(fd, buffer, result, &endline);
	buffer += endline;
	return (result);
}

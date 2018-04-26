/*
** EPITECH PROJECT, 2018
** PSU_tetris_2017
** File description:
** PSU_tetris_2017 made by Sanchez Lucas
*/

int my_tablen(char **str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

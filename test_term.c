/*
** EPITECH PROJECT, 2017
** PSU_42sh_2017
** File description:
** termcaps.c
*/

# include <pwd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
#include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/param.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

#define ERR 2048

int my_outc(int c)
{
  putchar(c);
  return (0);
}

void putstr(char *str)
{
  for (int i = 0; str[i]; i++)
    putchar(str[i]);
}

int     voir_touche()
{
  int bytes = 0;
  char key[5];
  char *line = calloc(0, sizeof(char) * 5);
  int i = 0;

  if (!line)
    exit (84);
  while (1) {
    bytes = read(0, key, 4);
    key[bytes] = 0;
    for (int i = 0; key[i]; i++)
      write(0, &key[i], 1);
  }
  return (0);
}


int              main(int ac, char **av, char **env)
{
  char           *name_term;

  struct termios term;
 term.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
term.c_cc[VMIN] = 1;
term.c_cc[VTIME] = 0;
  if ((name_term = getenv("TERM")) == NULL)
     return (-1);
  if (tgetent(NULL, name_term) == ERR)
     return (-1);
// On applique les changements :
if (tcsetattr(0, TCSADRAIN, &term) == -1)
return (-1);
  voir_touche();
return (0);
}

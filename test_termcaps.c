# include <pwd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <term.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/param.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct		s_tc
{
	char			buff[2048];
	char			tmp[2048];
	int				nbr_char;
	int				prompt_len;
	int				init_prompt_len;
	int				x_max;
	int				curs_x;
	int				curs_y;
	char			*up;
	char			*down;
	char			*right;
	char			*left;
	int				ctrl_r;
	int				stop;
	int				redim;
}					t_tc;

int	term_put(int c)
{
	write(1, &c, 1);
	return (0);
}

void	init_termcap(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) != 1) {
		printf("ERROR.\n");
		exit (84);
	}
	if (tcgetattr(0, &term) != 0) {
		printf("ERROR.\n");
		exit (84);
	}
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= (ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	if (tcsetattr(0, TCSANOW, &term) != 0){
		printf("ERROR.\n");
		exit (84);
	}
}

void	init_struct_termcap(t_tc *info, int prompt_len)
{
	struct winsize	*w;

	//ft_bzero(tool, sizeof(*tool)); //calloc
	info->up = tgetstr("up", NULL);
	info->down = tgetstr("sf", NULL);
	info->right = tgetstr("nd", NULL);
	info->left = tgetstr("le", NULL);
	w = calloc(0, sizeof(*w));
	if (ioctl(1, TIOCGWINSZ, w) != 0)
		info->x_max = tgetnum("co") - 1;
	else
		info->x_max = w->ws_col - 1;
	free(w);
	if (prompt_len >= info->x_max + 1) // si resize
	{
		info->prompt_len = prompt_len % (info->x_max + 1);
		if (prompt_len == info->x_max + 1 && info->redim == 0)
			tputs(info->down, 1, term_put);
	}
	else
		info->prompt_len = prompt_len;
	info->init_prompt_len = prompt_len;
	info->curs_x = info->prompt_len;
}


int		isprint_(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

void move_left(t_tc *info)
{
	if (info->curs_y == 0 && info->curs_x == info->prompt_len)
		tputs(tgetstr("bl", NULL), 1, term_put);
	else if (info->curs_x != 0)
	{
		tputs(info->left, 1, term_put);
		info->curs_x--;
	}
}

void basic(char *buff, t_tc *info)
{
	isprint_(buff[0]) == 1 ? putchar(buff[0]) : 0;

	//printf("debug : %d %d && %d\n", buff[0], buff[1], buff[2]);
	if (buff[0] == 0 && buff[1] == 91 && buff[2] == 68)
		move_left(info);
}

void	process_term(char *buff, t_tc *info)
{
	basic(buff, info);
}

int main ()
{
	struct termios	term_sys;
	char *buf = calloc(0, sizeof(char) * 127);
	int size = 0;
	t_tc *info_shell = malloc(sizeof(*info_shell));

//	while (1) {
		size = read (0, buf, 127);
		buf[size] = 0;
		init_termcap();
		while (1) {
			size = read (0, buf, 127);
			buf[size] = 0;
			process_term(buf, info_shell);
		}
		//#############################//
	//}
	return (0);
}
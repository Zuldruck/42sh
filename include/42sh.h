/*
** EPITECH PROJECT, 2018
** my exec 2
** File description:
** 42sh
*/

#ifndef	__42sh__
#define	__42sh__

#include "my.h"
#include <glob.h>

#define UNUSED(x) (void)(x)

typedef struct env_s env_t;
typedef struct btree_s btree_t;

typedef struct env_s {
	char *name;
	char *value;
	env_t *next;
} env_t;

typedef struct btree_s {
	char *op;
	char *cmd;
	int fd[2];
	btree_t *left;
	btree_t *right;
} btree_t;

typedef struct operator_s {
	char *op;
	void (*fptr)(btree_t *, env_t *, int *);
} operator_t;

env_t *global_env;

int count_args(char **);
void display_args(char **);
char *get_line(void);
void my_loop(env_t *, int);
char *get_dir(env_t *);
int my_exec(char **, env_t *, int *);
void my_exec_pipe(btree_t *, env_t *, int *, int *);
void print_prompt(env_t *);
int concat_exec(char **, env_t*);
int check_built_ins(char **, env_t *, int *, int *);
void unsetenv_func(char **, env_t *, int *);
void cd_func(char **, env_t *, int *);
void exit_func(char **, env_t *, int *);
void setenv_func(char **, env_t *, int *);
void echo_func(char **, env_t *, int *);
env_t *create_list(char **);
void env_func(char **, env_t *, int *);
char **list_to_2d_arr(env_t *);
char *get_env(env_t *, char *);
int find_command_size(char **);
env_t *fill_my_env(env_t *);
int verif_env(char **);
void sig_handler(int);
int check_segfault(int);
void free_list(env_t *);
void change_pwd(env_t *);
void free_btree_node(btree_t *);
btree_t *create_btree_node(char *, char *);
void parse_cmd(env_t *, char *, int *);
void display_btree(btree_t *);
void parse_cmd_for_pipes_and_redirections(btree_t *);
void parse_cmd_for_separator(btree_t *);
void exec_tree(btree_t *, env_t *, int *);
int set_pipefd(btree_t *);
void exec_semicolon(btree_t *, env_t *, int *);
void exec_double_and(btree_t *, env_t *, int *);
void exec_double_or(btree_t *, env_t *, int *);
void exec_pipe(btree_t *, env_t *, int *);
void exec_right_redirect(btree_t *, env_t *, int *);
void exec_double_right_redirect(btree_t *, env_t *, int *);
void exec_left_redirect(btree_t *, env_t *, int *);
void exec_double_left_redirect(btree_t *, env_t *, int *);
int redirect_error_handling(int, char **, env_t *, int *);
int btree_error_handling(btree_t *, int);

// GLOBBING
int process_globbing(char **cmd);
char *convert_tab_to_string(char **tab);
int check_wildcard(char *cmd);
char *parse_wildcard(char *cmd, int clean);
int count_wild(char *cmd);
int process_wildcard(char **cmd);


#endif /* __42sh__ */

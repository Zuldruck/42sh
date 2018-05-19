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
#include <ctype.h>

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

typedef struct builtin_s {
	char *name;
	void (*fptr)(char **, env_t *, int *);
} builtin_t;

env_t *global_env;

int count_args(char **cmd);
void display_args(char **cmd);
char *get_line(void);
void my_loop(env_t *env, int);
char *get_dir(env_t *env);
int my_exec(char **cmd, env_t *env, int *ret_value);
void my_exec_pipe(btree_t *, env_t *env, int *ret_value, int *fd);
void print_prompt(env_t *env);
char *concat_exec(char **cmd, env_t *env);
int check_built_ins(char **cmd, env_t *env, int *ret_value, int *fd);
void unsetenv_func(char **cmd, env_t *env, int *ret_value);
void cd_func(char **cmd, env_t *env, int *ret_value);
void where_func(char **cmd, env_t *env, int *ret_value);
void which_func(char **cmd, env_t *env, int *ret_value);
void exit_func(char **cmd, env_t *env, int *ret_value);
void setenv_func(char **cmd, env_t *env, int *ret_value);
void echo_func(char **cmd, env_t *env, int *ret_value);
env_t *create_list(char **cmd);
void env_func(char **cmd, env_t *env, int *ret_value);
char **list_to_2d_arr(env_t *env);
char *get_env(env_t *env, char *);
int find_command_size(char **cmd);
env_t *fill_my_env(env_t *env);
int verif_env(char **cmd);
void sig_handler(int);
int check_segfault(int);
void free_list(env_t *env);
void change_pwd(env_t *env);
void free_btree_node(btree_t *);
btree_t *create_btree_node(char *, char *);
void parse_cmd(env_t *env, char *, int *ret_value);
void display_btree(btree_t *tree);
int parse_cmd_for_pipes_and_redirections(btree_t *tree);
int parse_cmd_for_semicolon(btree_t *tree);
int parse_cmd_for_and(btree_t *node);
int parse_cmd_for_or(btree_t *node);
void exec_tree(btree_t *tree, env_t *env, int *ret_value);
int set_pipefd(btree_t *tree);
void exec_semicolon(btree_t *tree, env_t *env, int *ret_value);
void exec_double_and(btree_t *tree, env_t *env, int *ret_value);
void exec_double_or(btree_t *tree, env_t *env, int *ret_value);
void exec_pipe(btree_t *tree, env_t *env, int *ret_value);
void exec_right_redirect(btree_t *tree, env_t *env, int *ret_value);
void exec_double_right_redirect(btree_t *tree, env_t *env, int *ret_value);
void exec_left_redirect(btree_t *tree, env_t *env, int *ret_value);
void exec_double_left_redirect(btree_t *tree, env_t *env, int *ret_value);
int redirect_error_handling(int, char **cmd, env_t *env, int *ret_value);
int btree_error_handling(btree_t *tree, int);
int parse_env_variables(char **cmd, env_t *env, int *ret_value);
int check_quotes(char *cmd, int i);
int is_a_built_in(char *str);
int test_concat_exec(char *test_access, char **path, char **str);

// GLOBBING

int process_globbing(char **cmd);
char *convert_tab_to_string(char **tab);
int check_wildcard(char *cmd);
char *parse_wildcard(char *cmd, int clean);
int count_wild(char *cmd);
int process_glob(char **cmd);
int check_brackets(char *cmd);

// BUILTIN
void repeat_func(char **str, env_t *env, int *ret_value);
void if_func(char **str, env_t *env, int *ret_value);


#endif /* __42sh__ */

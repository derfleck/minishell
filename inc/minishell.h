#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <limits.h>

# include "types.h"
# include "parser.h"
# include "lexer.h"
# include "executor.h"
# include "expander.h"

/* functions env */
t_env		*init_env(char **envp);
t_env		*create_user_node(t_env **head);

void		add_node_to_list(t_env **head, t_env *new);
t_env		*find_env_node(t_env *head, char *key);
void		replace_node_value(t_env *node, char *new_value, t_env **head);
void		append_node_value(t_env *node, char *value2, t_env **head);

int			key_validity_check(char *key);
t_env		*create_node(char *str, t_env *head);
void		increase_shell_level(t_env **env);
char		*split_env_value(char *str);
char		*split_env_key(const char *str, t_env *head);

char		**create_env_arr(t_env *head);
void		reset_shlvl(t_env **head);
t_env		*create_home(char *str, t_env **head);

/* free */
void		*free_ptr(void *ptr);
void		*free_charray(char **arr);
void		perror_exit_free_env(char *message, t_env *head);
void		*free_env_list(t_env **head);

void		perror_exit_2(char *message, t_shell *sh, t_env **env, int mode);
void		perror_lexer(char *message, char *s, t_env *env, t_lexer *lex);
void		perror_cmd(char *message, t_cmd *cmd, t_env *head);
void		perror_shell(char *message, t_shell *sh);

void		perror_shell_no_env(char *message, t_shell *sh);
void		perror_cmd_not_found(char *cmd, t_shell *sh);
void		perror_env_too_big(char *cmd, t_shell *sh, t_env **head);

/* utils */
int			ft_strcmp(char *s1, char *s2);
int			ft_isnum(int c);
char		*safe_join(char *s1, char *s2, t_env *head);

/* Builtins */
int			helper_get_arg_count(char **args);
int			builtin_env(t_env *env, char **args);
int			builtin_pwd(t_env *head);
int			builtin_export(char **args, t_env **env);
int			builtin_unset(char **args, t_env **env);
int			builtin_cd(char **args, t_env **env);
int			builtin_exit(t_shell *sh, char **args, t_env **env, int process);
int			builtin_echo(char **args, t_env *head);

/* signals for ctrl+(D || C || \) */
void		set_sigaction(int i);
void		handle_ctrlc(int sig);
void		handle_signals_child(int signum);

#endif

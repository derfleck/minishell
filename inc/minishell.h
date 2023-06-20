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
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

# include "types.h"
# include "parser.h"
# include "lexer.h"
# include "executor.h"
# include "expander.h"

/* functions env */
t_env		*init_env(char **envp);
t_env		*create_node(char *str, t_env *head);
int			get_list_size(char **envp);
int			print_env(t_env *env);
t_env		*create_env(t_env *head);
t_env		*create_user_node(t_env *head);
char		**create_env_arr(t_env *head);
void		copy_list_to_arr(t_env *head, char **env_arr);
int			return_list_size(t_env *head);

/* list functions */
t_env		*returnlast_env(t_env *lst);
t_env		*find_env_node(t_env *head, char *key);
char		*split_env_value(char *str);
char		*split_env_key(const char *str, t_env *head);
void		replace_node_value(t_env *node, char *new_value, t_env *head);
void		append_node_value(t_env *node, char *value2, t_env *head);
void		remove_node(t_env **head, char *key);
void		add_node_to_list(t_env *head, t_env *new);
int			key_validity_check(char *key);

/* exit */
void		*free_ptr(void *ptr);
void		perror_exit(char *message);
void		perror_lexer(char *message, char *s, t_env *env, t_lexer *lex);
void		perror_cmd(char *message, t_cmd *cmd, t_env *head);
void		perror_shell(char *message, t_shell *sh);
void		perror_shell_no_env(char *message, t_shell *sh);
void		perror_exit_free_env(char *message, t_env *head);

/* utils */
int			ft_strcmp(char *s1, char *s2);
int			ft_isnum(int c);
void		increase_shell_level(t_env *env);

/* Builtins */
void		perror_exit(char *message);
int			builtin_pwd(t_env *head);
void		set_env_command(t_env *head);
int			helper_get_arg_count(char **args);
int			builtin_export(char **args, t_env *env);
int			builtin_unset(char **args, t_env **env);
int			builtin_cd(char **args, t_env *env);
int			builtin_exit(t_shell *sh, char **args, t_env *env, int process);
void		exit_parent(t_shell *sh, char **args, t_env *head, int argc);
void		*free_env_list(t_env *head);
void		*free_env_node(t_env *node);
void		builtin_echo(char **args, t_env *head);

/* signals for ctrl+(D || C || \) */
void		set_sigaction(int i);
void		handle_ctrlc(int sig);
void		handle_signals_child(int signum);

#endif

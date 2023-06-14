#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "lexer.h"

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

/* Macros */
# ifndef PARENT
#  define PARENT 1
# endif
# ifndef CHILD
#  define CHILD 0
# endif
# ifndef HOME
#  define HOME ".."
# endif

/* global variable for exit status */
extern int	g_stat;

/* List for env */
typedef struct s_env
{
	char			*key_value;
	struct s_env	*next;
}	t_env;

//struct for the whole shell, which points to essential values
//process list, wait status information and environment variables
typedef struct s_shell
{
	pid_t	*pid;
	int		wstatus;
	char	**envp;
	char	**paths;
	int		stdin_cpy;
	t_env	*env;
	t_cmd	*cmd_start;
	char	*s;
}	t_shell;

# include "executor.h"
# include "expander.h"

/* functions env */
t_env		*init_env(char **envp);
t_env		*create_node(char *str);
int			get_list_size(char **envp);
void		print_env(t_env *env);
char		*create_env(void);
char		**create_env_arr(t_env *head);
void		copy_list_to_arr(t_env *head, char **env_arr);
int			return_list_size(t_env *head);

/* list functions */
t_env		*returnlast_env(t_env *lst);
t_env		*find_env_node(t_env *head, char *key);
char		*split_env_value(char *str);
char		*split_env_key(const char *str);
void		replace_node_value(t_env *node, char *new_value);
void		append_node_value(t_env *node, char *value2);
void		remove_node(t_env *head, char *key);
void		add_node_to_list(t_env *head, t_env *new);
int			key_validity_check(char *key);

/* env tester */
void		env_tester(char *key, t_env *env);

/* exit */
void		*free_ptr(void *ptr);
void		perror_exit(char *message);

/* utils */
int			ft_strcmp(char *s1, char *s2);
int			ft_isnum(int c);

/* Builtins */
void		builtin_pathfinder(t_env *env, t_cmd *cmd);
void		builtin_pwd(void);
int			helper_get_arg_count(char **args);
void		builtin_export(char **args, t_env *env);
int			export_isequal(char *arg);
void		export_append_helper(char *key, char *str, t_env *env);
void		builtin_unset(char **args, t_env *env);
void		builtin_cd(char **args, t_env *env);
void		cd_go_home(t_env *env, char *str);
void		update_pwds(t_env *env, char *oldpath);
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

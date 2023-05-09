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

/* functions env */
t_env		*init_env(char **envp);
t_env		*create_node(char *str);
int			get_list_size(char **envp);
void		print_env(t_env *env);
char		*create_env(void);

/* list functions */
t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*find_env_node(t_env **head, char *key);
char		*split_env_value(char *str);
char		*split_env_key(const char *str);
t_env		*replace_node_value(t_env *node, char *new_value);
void		remove_node(t_env **head, char *key);
void		add_node_to_list(t_env **head, t_env *node);

/* env tester */
void		env_tester(char *key, t_env **env);

/* utils */
void		*free_ptr(void *ptr);

/* Builtins */
void		builtin_export(char *str, t_env *env);
void		builtin_unset(char *str, t_env *env);
int			builtin_cd(char *str, t_env *env);
void		update_pwds(t_env *env, char *oldpath);

/* signals for ctrl+(D || C || \) */
void		set_sigaction(int i);
void		handle_ctrlc(int sig);
void		handle_signals_child(int signum);

#endif

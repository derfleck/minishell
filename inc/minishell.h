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

//types for classifiying tokens in lexer
typedef enum s_type {
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_type;

//enum for categorizing tokens in parser
typedef enum s_parse {
	FILE_IN = 1, // < character
	HERE_DOC, // <<
	FILE_OUT, // > character
	FILE_APP, // >>
	INPUT_FILE, //name after FILE_IN
	STOP_WORD, //word to stop HERE_DOC
	OUT_FILE, //file to write to after >
	APP_FILE //file to append to after >>
}	t_parse;

//doubly linked list for lexer
typedef struct s_lexer {
	char			*str;
	t_type			token;
	int				i;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

//functions for lexer
t_type		classify_token(char	*str);
t_type		check_token(char c);
int			syntax_check(char *str);
int			count_char(char *str, char c);
int			skip_quotes(char *str);

//functions for splitting line
void		empty_set(char **str);
char		**ft_split_set(char *str, char *set);

//functions for creating lexer list
t_lexer		*start_lexer(char *str);

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
t_env		*find_env_node(t_env **env, char *key);
char		*split_env_value(char *str);
char		*split_env_key(const char *str);
t_env		*replace_node(t_env *node, char *new_value);

/* env tester */
void	env_tester(char *key, t_env **env);

/* utils */
void		*free_ptr(void *ptr);

/* signals for ctrl+(D || C || \) */
void		set_sigaction(int i);
void		handle_ctrlc(int sig);
void		handle_signals_child(int signum);


#endif

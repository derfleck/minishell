#ifndef TYPES_H
# define TYPES_H

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
# ifndef ARG_MAX
#  define ARG_MAX 4096
# endif
# ifndef HEREDOC_WARN
#  define HEREDOC_WARN "minishell: warning : here-document delimited by \
end-of-file (wanted `%s')\n"
# endif
# ifndef TOKEN_WARN_NEW
#  define TOKEN_WARN_NEW "minishell: syntax error near unexpected token \
`newline'"
# endif
# ifndef TOKEN_WARN_CHR
#  define TOKEN_WARN_CHR "minishell: syntax error near unexpected token "
# endif

/* global variable for exit status */
extern int	g_stat;

/* List for env */
typedef struct s_env
{
	char			*key_value;
	struct s_env	*next;
}	t_env;

//types for classifiying tokens in lexer
typedef enum s_type {
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_type;

//linked list for lexer
typedef struct s_lexer {
	char			*str;
	t_type			token;
	int				i;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

//values for iterating through num array
typedef enum s_num {
	CMD = 0,
	ARG,
	HERE
}	t_num;

//values for fd array in cmd struct
typedef enum s_fd {
	IN = 0,
	OUT
}	t_fd;

//num array contains number of strings for each part of the struct
//index for num array in t_num struct, e.g. num[HERE] gives you
//the number of heredoc stopwords
typedef struct s_cmd {
	char			*cmd;
	char			**arg;
	char			**here;
	char			*here_file;
	t_lexer			*in;
	t_lexer			*out;
	t_lexer			*start;
	int				num[3];
	int				fd[2];
	int				i;
	struct s_cmd	*next;
	t_env			*head;
}	t_cmd;

//struct for the whole shell, which points to essential values
//process list, wait status information and environment variables
typedef struct s_shell
{
	pid_t	*pid;
	int		wstatus;
	char	**envp;
	char	**paths;
	int		stdin_cpy;
	t_env	*head;
	t_cmd	*cmd_start;
	char	*s;
}	t_shell;

#endif
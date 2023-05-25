#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include "minishell.h"

//struct for the whole shell, which points to essential values
//process list, wait status information and environment variables
typedef struct s_shell
{
	pid_t	*pid;
	int		wstatus;
	char	**envp;
	char	**paths;
}	t_shell;

int		open_files(t_lexer *lex);

void	*safe_free(void	*ptr);

t_shell	*init_shell(t_cmd *cmd, t_env **head);

char    *get_cmd_with_path(t_cmd *cmd, char **path);
char    **get_paths(char **envp);

#endif
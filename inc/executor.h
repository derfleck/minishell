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
	int		stdin_cpy;
	t_env	**env;
}	t_shell;

//exec multiple
int		cmd_with_pipes(t_shell *shell, t_cmd *cmd);
int		fork_and_exec(int *pip, t_cmd *cmd, t_shell *shell, int i);
int		child_redir(int *pip, t_cmd *cmd, t_shell *shell);
int		parent_redir(int *pip, t_cmd *cmd);

//exec
void	execute_cmd(t_cmd *cmd, t_shell *shell);
t_shell	*init_shell(t_cmd *cmd, t_env *head);

//utils
void	*safe_free(void	*ptr);
pid_t   *wait_children(t_shell *shell, int cmd);
t_cmd	*free_cmd(t_cmd *cmd);
t_lexer	*free_lex(t_lexer *lex);

//open check
int		open_files(t_cmd *cmd);
void	open_in_out(t_cmd *cmd);

//search path
char	**get_paths(char **envp);
char    *get_cmd_with_path(t_cmd *cmd, char **path);

//single cmd
void	exec_single_cmd(t_cmd *cmd, t_shell *shell);

//heredoc
void	run_heredoc(t_cmd *cmd);
int		unlink_heredoc(t_cmd *cmd);

#endif
#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "types.h"

//exec multiple
int		cmd_with_pipes(t_shell *shell, t_cmd *cmd, t_env **env);
int		fork_and_exec(int *pip, t_cmd *cmd, t_shell *shell, int i, t_env **env);
int		child_redir(int *pip, t_cmd *cmd, t_shell *shell, t_env **env);
int		parent_redir(int *pip, t_cmd *cmd);

//exec
void	execute_cmd(t_cmd *cmd, t_shell *shell, t_env **head, int mode);
void	init_shell(char *s, t_cmd *cmd, t_env **head);
int		is_builtin(t_cmd *cmd);

//utils
void	*safe_free(void	*ptr);
pid_t	*wait_children(t_shell *shell, int cmd);
t_cmd	*free_cmd(t_cmd *cmd);
t_lexer	*free_lex(t_lexer *lex);
t_shell	*free_shell(t_shell *sh);

//open check
int		open_files(t_cmd *cmd);
void	open_in_out(t_cmd *cmd);

//search path
char	**get_paths(char **envp);
char    *get_cmd_with_path(t_cmd *cmd, char **path);

//single cmd
void	exec_single_cmd(t_cmd *cmd, t_shell *shell, t_env **head);

//heredoc
void	run_heredoc(t_cmd *cmd);
int		unlink_heredoc(t_cmd *cmd);

#endif
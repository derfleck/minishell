#include "../../inc/minishell.h"

//closes custom redirections and redirect read end
//of shared pipe to STDIN of parent process
int	parent_redir(int *pip, t_cmd *cmd)
{
	if (cmd->in != NULL)
		close(cmd->fd[IN]);
	if (cmd->out != NULL)
		close(cmd->fd[OUT]);
	if (cmd->next != NULL)
	{
		close(pip[1]);
		if (dup2(pip[0], STDIN_FILENO) == -1)
			return (0);
		close(pip[0]);
	}
	return (1);
}

//redirects write end of pipe to STDOUT if not last cmd
//redirects in and out files to STDIN/STDOUT respectively
int	child_redir(int *pip, t_cmd *cmd, t_shell *shell, t_env **env)
{
 	if (cmd->next != NULL)
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
			return (0);
		close(pip[1]);
		close(pip[0]);
	}
	if (dup2(cmd->fd[IN], STDIN_FILENO) == -1)
		return (0);
	if (cmd->in != NULL)
		close(cmd->fd[IN]);
	if (dup2(cmd->fd[OUT], STDOUT_FILENO) == -1)
		return (0);
	if (cmd->out != NULL)
		close(cmd->fd[OUT]);
	close(shell->stdin_cpy);
	execute_cmd(cmd, shell, env, CHILD);
	return (1);
}

//creates fork of process and checks if parent/child process
int	fork_and_exec(int *pip, t_cmd *cmd, t_shell *shell, int i, t_env **env)
{
	if (cmd->next != NULL)
	{
		if (pipe(pip) == -1)
			return (0);
	}
	shell->pid[i] = fork();
	set_sigaction(shell->pid[i]);
	if (shell->pid[i] < 0)
		return (0);
	if (shell->pid[i] == CHILD)
		return (child_redir(pip, cmd, shell, env));
	else
		return (parent_redir(pip, cmd));
	return (1);
}

//executes piped commands and initializes redirects
//returns 1 on success, 0 on failure
//starting point for piped execution
int	cmd_with_pipes(t_shell *shell, t_cmd *cmd, t_env **env)
{
	int		pip[2];
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	shell->stdin_cpy = dup(STDIN_FILENO);
	i = 0;
	run_heredoc(cmd);
	while (tmp)
	{
		if (open_files(tmp))
			open_in_out(tmp);
		else
			break ;
		if (!fork_and_exec(pip, tmp, shell, i++, env))
			break ;
		unlink_heredoc(tmp);
		tmp = tmp->next;
	}
	dup2(shell->stdin_cpy, STDIN_FILENO);
	close(shell->stdin_cpy);
	wait_children(shell, i);
	return (1);
}

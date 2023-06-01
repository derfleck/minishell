#include "../../inc/minishell.h"

void	exec_single_cmd(t_cmd *cmd, t_shell *shell)
{
	if (open_files(cmd->start))
		open_in_out(cmd);
	else
		return ;
	shell->pid[0] = fork();
	if (shell->pid[0] == CHILD)
	{
		if (dup2(cmd->fd[IN], STDIN_FILENO) == -1)
			return ;
		if (dup2(cmd->fd[OUT], STDOUT_FILENO) == -1)
			return ;
		execute_cmd(cmd, shell);
	}
	else
	{
		if (cmd->in)
			close(cmd->fd[IN]);
		if (cmd->out)
			close(cmd->fd[OUT]);
		shell->pid = wait_children(shell, 1);
	}
}

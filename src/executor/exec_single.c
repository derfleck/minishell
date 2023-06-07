#include "../../inc/minishell.h"

void	exec_single_cmd(t_cmd *cmd, t_shell *shell)
{
	run_heredoc(cmd);
	if (open_files(cmd))
		open_in_out(cmd);
	else
		return ;
	shell->pid[0] = fork();
	set_sigaction(shell->pid[0]);
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
	unlink_heredoc(cmd);
}

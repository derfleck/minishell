#include "../../inc/minishell.h"

//checks if command is one that needs to affect parent process
static int	check_builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0 || \
		ft_strncmp(cmd->cmd, "exit", 4) == 0 || \
		ft_strncmp(cmd->cmd, "export", 6) == 0 || \
		ft_strncmp(cmd->cmd, "unset", 5) == 0)
		return (1);
	return (0);
}

//helper, handles forking, redirection and execution
static void	exec_child_single(t_cmd *cmd, t_shell *shell, t_env **head)
{
	shell->pid[0] = fork();
	set_sigaction(shell->pid[0]);
	if (shell->pid[0] == CHILD)
	{
		if (dup2(cmd->fd[IN], STDIN_FILENO) == -1)
			return ;
		if (dup2(cmd->fd[OUT], STDOUT_FILENO) == -1)
			return ;
		execute_cmd(cmd, shell, head, CHILD);
		free_shell(shell);
	}
	else
	{
		if (cmd->in)
			close(cmd->fd[IN]);
		if (cmd->out)
			close(cmd->fd[OUT]);
		wait_children(shell, 1);
		unlink_heredoc(cmd);
		shell = free_shell(shell);
	}
}

void	exec_single_cmd(t_cmd *cmd, t_shell *shell, t_env **head)
{
	run_heredoc(cmd);
	if (open_files(cmd))
		open_in_out(cmd);
	else
		return ;
	if (check_builtins(cmd))
	{
		execute_cmd(cmd, shell, head, PARENT);
		unlink_heredoc(cmd);
	}
	else
		exec_child_single(cmd, shell, head);	
}

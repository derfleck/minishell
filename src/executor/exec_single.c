#include "../../inc/minishell.h"

//checks if command is one that needs to affect parent process
static int	check_builtins(t_cmd *cmd)
{
	if (cmd->cmd && \
		(ft_strncmp(cmd->cmd, "cd", 2) == 0 || \
		ft_strncmp(cmd->cmd, "exit", 4) == 0 || \
		ft_strncmp(cmd->cmd, "export", 6) == 0 || \
		ft_strncmp(cmd->cmd, "unset", 5) == 0))
		return (1);
	return (0);
}

//updates last cmd path in environment variables (_)
static void	set_last_cmd_path(t_cmd *cmd, t_shell *sh, t_env **head)
{
	char	**path;
	char	*tmp;

	tmp = NULL;
	if (!cmd->cmd)
		return ;
	path = malloc(sizeof(char *) * 2);
	if (is_builtin(cmd->cmd))
		*path = ft_strjoin("_=/usr/bin/", cmd->cmd);
	else
	{
		tmp = get_cmd_with_path(cmd, sh->paths);
		*path = ft_strjoin("_=", tmp);
		free(tmp);
	}
	path[1] = NULL;
	builtin_export(path, head);
	free(path[0]);
	free(path);
}

static void	child_helper(t_cmd *cmd, t_shell *shell, t_env **head)
{
	open_check(cmd, shell, head);
	if (dup2(cmd->fd[IN], STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(cmd->fd[OUT], STDOUT_FILENO) == -1)
		perror("dup2");
	execute_cmd(cmd, shell, head, CHILD);
	if (head != NULL)
		head = free_env_list(head);
	if (shell != NULL)
		shell = free_shell(shell);
	exit (0);
}

//helper, handles forking, redirection and execution
static void	exec_child_single(t_cmd *cmd, t_shell *shell, t_env **head)
{
	shell->pid[0] = fork();
	if (cmd->cmd && ft_strlen(cmd->cmd) > ft_strlen("/minishell") && \
		!ft_strncmp(&cmd->cmd[ft_strlen(cmd->cmd) - 10], "/minishell", 10))
		set_sigaction(-1);
	else
		set_sigaction(shell->pid[0]);
	if (shell->pid[0] == CHILD)
		child_helper(cmd, shell, head);
	else
	{
		if (cmd->in && cmd->fd[IN] != STDIN_FILENO)
			close(cmd->fd[IN]);
		if (cmd->out && cmd->fd[OUT] != STDOUT_FILENO)
			close(cmd->fd[OUT]);
		wait_children(shell, 1);
		if (g_stat == 0)
			set_last_cmd_path(cmd, shell, head);
		unlink_heredoc(cmd);
	}
}

void	exec_single_cmd(t_cmd *cmd, t_shell *shell, t_env **head)
{
	if (run_heredoc(shell, cmd))
		return (perror_heredoc(shell));
	if (check_builtins(cmd))
	{
		execute_cmd(cmd, shell, head, PARENT);
		unlink_heredoc(cmd);
	}
	else
		exec_child_single(cmd, shell, head);
}

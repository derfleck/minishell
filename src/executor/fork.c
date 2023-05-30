#include "../../inc/executor.h"

//frees t_cmd struct, checks if values exist before freeing
void	free_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->cmd)
		cmd = safe_free(cmd->cmd);
	while(i < cmd->num[ARG])
		free(cmd->arg[i++]);
	i = 0;
	while(i < cmd->num[HERE])
		free(cmd->here[i++]);
	if (cmd->arg)
		cmd->arg = safe_free(cmd->arg);
	if (cmd->here)
		cmd->here = safe_free(cmd->here);
}

//frees lexer list node by node
void	free_lex(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		tmp = lex->next;
		free(lex);		
	}
}

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
int	child_redir(int *pip, t_cmd *cmd, t_shell *shell)
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
	execute_cmd(cmd, shell);
	return (1);
}

int	fork_and_exec(int *pip, t_cmd *cmd, t_shell *shell, int i)
{
	if (cmd->next != NULL)
	{
		if (pipe(pip) == -1)
			return (0);
	}
	shell->pid[i] = fork();
	if (shell->pid[i] < 0)
		return (0);
	if (shell->pid[i] == 0)
	{
		if (!child_redir(pip, cmd, shell))
			return (0);
	}
	else
	{
		if (!parent_redir(pip, cmd))
			return (0);
	}
	return (1);
}

//executes piped commands and initializes redirects
//returns 1 on success, 0 on failure
int	cmd_with_pipes(t_shell *shell, t_cmd *cmd)
{
	int		pip[2];
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		if (!fork_and_exec(pip, tmp, shell, i++))
			return (0);
		tmp = tmp->next;
	}
	shell->pid = wait_children(shell, cmd->num[CMD]);
	return (1);
}

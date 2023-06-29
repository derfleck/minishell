/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:33:35 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/29 12:33:38 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//closes custom redirections and redirect read end
//of shared pipe to STDIN of parent process
int	parent_redir(int *pip, t_cmd *cmd)
{
	if (cmd->in != NULL && g_stat != 1)
		close(cmd->fd[IN]);
	if (cmd->out != NULL && g_stat != 1)
		close(cmd->fd[OUT]);
	if (cmd->next != NULL)
	{
		close(pip[1]);
		if (dup2(pip[0], STDIN_FILENO) == -1)
			perror("dup2");
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
			perror("dup2");
		close(pip[1]);
		close(pip[0]);
	}
	if (dup2(cmd->fd[IN], STDIN_FILENO) == -1)
		perror("dup2");
	if (cmd->in != NULL)
		close(cmd->fd[IN]);
	if (dup2(cmd->fd[OUT], STDOUT_FILENO) == -1)
		perror("dup2");
	if (cmd->out != NULL)
		close(cmd->fd[OUT]);
	close(shell->stdin_cpy);
	if (g_stat == 1)
	{
		free_env_list(env);
		free_shell(shell);
		exit (1);
	}
	execute_cmd(cmd, shell, env, CHILD);
	return (1);
}

//creates fork of process and checks if parent/child process
int	fork_and_exec(int *pip, t_cmd *cmd, t_shell *shell, int i)
{
	if (cmd->next != NULL)
	{
		if (pipe(pip) == -1)
			return (0);
	}
	open_check(cmd);
	shell->pid[i] = fork();
	set_sigaction(shell->pid[i]);
	if (shell->pid[i] < 0)
		return (0);
	if (shell->pid[i] == CHILD)
		child_redir(pip, cmd, shell, &shell->head);
	else
		parent_redir(pip, cmd);
	return (1);
}

static void	unlink_helper(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		unlink_heredoc(tmp);
		tmp = tmp->next;
	}
}

//executes piped commands and initializes redirects
//returns 1 on success, 0 on failure
//starting point for piped execution
int	cmd_with_pipes(t_shell *shell, t_cmd *cmd)
{
	int		pip[2];
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	shell->stdin_cpy = dup(STDIN_FILENO);
	i = 0;
	if (run_heredoc(shell, cmd))
		return (perror_heredoc(shell), 0);
	while (tmp)
	{
		if (!fork_and_exec(pip, tmp, shell, i++))
			break ;
		tmp = tmp->next;
	}
	dup2(shell->stdin_cpy, STDIN_FILENO);
	close(shell->stdin_cpy);
	wait_children(shell, i);
	unlink_helper(cmd);
	return (1);
}

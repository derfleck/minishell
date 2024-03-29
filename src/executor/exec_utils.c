/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:35:11 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/29 12:35:12 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//checks if command is a builtin
int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 3) == 0 || \
		ft_strncmp(cmd, "env", 3) == 0 || \
		ft_strncmp(cmd, "cd", 2) == 0 || \
		ft_strncmp(cmd, "export", 6) == 0 || \
		ft_strncmp(cmd, "unset", 5) == 0 || \
		ft_strncmp(cmd, "exit", 4) == 0 || \
		ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else
		return (0);
}

//waits for children to exit and sets status code
//frees pid_t struct for all created processes
pid_t	*wait_children(t_shell *shell, int cmd)
{
	int	i;
	int	sigq;

	i = 0;
	sigq = 0;
	while (i < cmd)
	{
		if (waitpid(shell->pid[i], &shell->wstatus, 0) == -1)
			return (NULL);
		if (!sigq && WIFSIGNALED(shell->wstatus))
			sigq = WTERMSIG(shell->wstatus) + 128;
		i++;
	}
	if (WIFEXITED(shell->wstatus))
		g_stat = WEXITSTATUS(shell->wstatus);
	else if (WIFSIGNALED(shell->wstatus))
		g_stat = WTERMSIG(shell->wstatus) + 128;
	if (sigq == 131 && g_stat == 131)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	else if (sigq == 130)
		write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

//frees t_cmd struct, checks if values exist before freeing
t_cmd	*free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp && tmp->start != NULL)
		free_lex(tmp->start);
	while (tmp)
	{
		if (tmp->arg != NULL)
			tmp->arg = free_ptr(tmp->arg);
		if (tmp->here != NULL)
			tmp->here = free_ptr(tmp->here);
		if (tmp->here_file != NULL)
			tmp->here_file = free_ptr(tmp->here_file);
		tmp = tmp->next;
	}
	return (free_ptr(cmd));
}

//frees lexer list node by node
t_lexer	*free_lex(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->str != NULL)
			tmp->str = free_ptr(tmp->str);
		tmp = tmp->next;
	}
	return (free_ptr(lex));
}

t_shell	*free_shell(t_shell *sh)
{
	int	i;

	if (sh)
	{
		if (sh->cmd_start != NULL && sh->cmd_start->start != NULL)
			sh->cmd_start->start = free_lex(sh->cmd_start->start);
		if (sh->cmd_start != NULL)
			sh->cmd_start = free_cmd(sh->cmd_start);
		i = -1;
		while (sh->envp && sh->envp[++i] != NULL)
			sh->envp[i] = free_ptr(sh->envp[i]);
		if (sh->envp)
			sh->envp = free_ptr(sh->envp);
		i = -1;
		while (sh->paths && sh->paths[++i] != NULL)
			sh->paths[i] = free_ptr(sh->paths[i]);
		if (sh->paths != NULL)
			sh->paths = free_ptr(sh->paths);
		if (sh->pid != NULL)
			sh->pid = free_ptr(sh->pid);
		if (sh->s != NULL)
			sh->s = free_ptr(sh->s);
		return (free_ptr(sh));
	}
	return (NULL);
}

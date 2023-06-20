#include "../../inc/minishell.h"

//this function ensures that the value of the pointer is overwritten with NULL after freeing it
void	*safe_free(void	*ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

//waits for children to exit and sets status code
//frees pid_t struct for all created processes
pid_t   *wait_children(t_shell *shell, int cmd)
{
	int	i;

	i = 0;
	while (i < cmd)
	{
		if(waitpid(shell->pid[i], &shell->wstatus, 0) == -1)
			return (NULL);
		i++;
	}
	if (WIFEXITED(shell->wstatus))
		g_stat = WEXITSTATUS(shell->wstatus);
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
			tmp->arg = safe_free(tmp->arg);
		if (tmp->here != NULL)
			tmp->here = safe_free(tmp->here);
		tmp = tmp->next;
	}
	return (safe_free(cmd));
}

//frees lexer list node by node
t_lexer	*free_lex(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->str != NULL)
			tmp->str = safe_free(tmp->str);
		tmp = tmp->next;		
	}
	return (safe_free(lex));
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
		while (sh->envp[++i] != NULL)
			sh->envp[i] = safe_free(sh->envp[i]);
		if (sh->envp)
			sh->envp = safe_free(sh->envp);
		i = -1;
		while (sh->paths[++i] != NULL)
			sh->paths[i] = safe_free(sh->paths[i]);
		if (sh->paths)
			sh->paths = safe_free(sh->paths);
		if (sh->pid != NULL)
			sh->pid = safe_free(sh->pid);
		if (sh->s != NULL)
			sh->s = safe_free(sh->s);
		return (safe_free(sh));
	}
	return (NULL);
}

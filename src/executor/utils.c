#include "../../inc/minishell.h"

//pid_t   *create_children()

//this function ensures that the value of the pointer is overwritten with NULL after freeing it
void	*safe_free(void	*ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

//waits for children to exit and sets status code
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
	shell->pid = safe_free(shell->pid);
	return (shell->pid);
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
/*
void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		i = -1;
		if (tmp->cmd != NULL)
			tmp->cmd = safe_free(tmp->cmd);
		while(tmp->arg[++i] != NULL)
			free(tmp->arg[i]);
		i = -1;
		while(tmp->here[++i] != NULL)
			free(tmp->here[i]);
		if (tmp->arg != NULL)
			tmp->arg = safe_free(tmp->arg);
		if (tmp->here != NULL)
			tmp->here = safe_free(tmp->here);
		tmp = tmp->next;
	}
	free(cmd);
}
*/

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

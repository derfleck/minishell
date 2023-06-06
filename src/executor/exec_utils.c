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
	i = 0;
	while (shell->envp[i])
		free(shell->envp[i++]);
	i = 0;
	while (shell->paths[i])
		free(shell->paths[i++]);
	shell->envp = safe_free(shell->envp);
	shell->paths = safe_free(shell->paths);
	return (safe_free(shell->pid));
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

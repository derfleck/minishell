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
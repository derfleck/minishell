#include "../../inc/minishell.h"

void	*free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

void	perror_exit_free_env(char *message, t_env *head)
{
	if (message)
		perror(message);
	free_env_list(head);
	exit (1);
}

//TODO: needs to free everything!!!
void	perror_exit(char *message)
{
	if (message)
		perror(message);
	//free_env_list(head);
	exit (1);
}
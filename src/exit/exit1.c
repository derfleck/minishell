#include "../../inc/minishell.h"

void	*free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

void	perror_exit(char *message)
{
	if (message)
		perror(message);
	exit (1);
}
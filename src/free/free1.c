#include "../../inc/minishell.h"

/* Safely frees a pointer */
void	*free_ptr(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

/* Frees a character array */
void	*free_charray(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		arr[i] = free_ptr(arr[i]);
		i++;
	}
	if (arr != NULL)
		arr = free_ptr(arr);
	return (NULL);
}

/* frees environment list and exits with code 1 */
void	perror_exit_free_env(char *message, t_env *head)
{
	if (message != NULL)
		perror(message);
	if (head != NULL)
		head = free_env_list(&head);
	exit (1);
}

/* static helper of free_env_list
Frees a single env node */
static void	*free_env_node(t_env *node)
{
	t_env	*tmp;

	if (!node)
		return (NULL);
	node->key_value = free_ptr(node->key_value);
	tmp = node->next;
	node = free_ptr(node);
	return (tmp);
}

/* Frees totality of env list */
void	*free_env_list(t_env **head)
{
	t_env	*node;

	if (head == NULL)
		return (NULL);
	node = *head;
	while (node)
		node = free_env_node(node);
	head = NULL;
	return (NULL);
}

void	perror_heredoc(t_shell *sh)
{
	t_cmd	*tmp;

	tmp = sh->cmd_start;
	while (tmp)
	{
		unlink_heredoc(tmp);
		tmp = tmp->next;
	}
}
#include "../../inc/minishell.h"

/* Counts list size, allocates and fills in new array to be returned */
char	**create_env_arr(t_env **head)
{
	int		size;
	char	**env_arr;

	size = return_list_size(head);
	env_arr = malloc (sizeof (char *) * size + 1);
	if (!env_arr)
		perror_exit("Malloc failed\n");
	copy_list_to_arr(head, env_arr);
	return (env_arr);
}

/* Copier to add strings to array one by one */
void	copy_list_to_arr(t_env **head, char **env_arr)
{
	t_env	*node;
	int		i;

	if (!head)
		return ;
	node = (*head);
	i = 0;
	while (node)
	{
		env_arr[i] = ft_strdup(node->key_value);
		if (!env_arr[i])
			perror_exit("Malloc failed\n");
		i++;
		node = node->next;
	}
	env_arr[i] = NULL;
}

/* Counts nodes of list, returns it as int */
int	return_list_size(t_env **head)
{
	t_env	*node;
	int		i;

	if (!head)
		return (0);
	i = 0;
	node = (*head);
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

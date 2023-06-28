#include "../../inc/minishell.h"

/* Copier to add strings to array one by one */
static void	copy_list_to_arr(t_env *head, char **env_arr)
{
	t_env	*node;
	int		i;

	node = head;
	i = 0;
	while (node)
	{
		env_arr[i] = ft_strdup(node->key_value);
		if (!env_arr[i])
			perror_exit_free_env("Malloc failed\n", head);
		i++;
		node = node->next;
	}
	env_arr[i] = NULL;
}

/* Counts nodes of list, returns it as int */
static int	return_list_size(t_env *head)
{
	t_env	*node;
	int		i;

	i = 0;
	node = head;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

/* Counts list size, allocates and fills in new array to be returned */
char	**create_env_arr(t_env *head)
{
	int		size;
	char	**env_arr;

	size = return_list_size(head);
	env_arr = ft_calloc(size + 1, sizeof(char *));
	if (!env_arr)
		perror_exit_free_env("Malloc failed\n", head);
	copy_list_to_arr(head, env_arr);
	return (env_arr);
}

/* sets SHLVL var to 0 when called */
int	reset_shlvl(t_env **head)
{
	t_env	*node;

	node = find_env_node(*head, "SHLVL");
	replace_node_value(node, "0", head);
	return (1);
}

/* Creates new HOME env node in case HOME was unset.
Important for Expander! (~) */
t_env	*create_home(char *str, t_env **head)
{
	t_env	*node;

	node = create_node(str, *head);
	add_node_to_list(head, node);
	node->next = NULL;
	return (node);
}

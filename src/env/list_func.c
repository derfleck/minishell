#include "../../inc/minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*end;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			end = ft_lstlast_env(*lst);
			end->next = new;
		}
	}
}

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*lst2;

	if (!lst)
		return ((t_env *)lst);
	lst2 = (t_env *)lst;
	while (lst2->next)
	{
		lst2 = lst2->next;
	}
	return (lst2);
}

t_env	*find_env_node(t_env **head, char *key)
{
	t_env	*node;

	if (head == NULL)
		return (NULL);
	node = *head;
	while (node && ft_strncmp(node->key_value, key, ft_strlen(key)))
		node = node->next;
	return (node);
}

/* Gets env node and char* to replace the current value (string after the first '=' sign ). */
void	replace_node_value(t_env *node, char *new_value)
{
	char	*k;
	char	*key;

	if (node == NULL)
		return ;
	k = split_env_key(node->key_value);
	key = ft_strjoin(k, "=");
	if (!k || !key)
		perror_exit("Malloc failed\n");
	free(k);
	node->key_value = free_ptr(node->key_value);
	node->key_value = ft_strjoin(key, new_value);
	if (node->key_value == NULL)
		perror_exit("Malloc failed\n");
	free(key);
}

/* Gets env node and char* to append it to the existing value. */
void	append_node_value(t_env *node, char *value2)
{
	char	*new_value;

	new_value = ft_strjoin(split_env_value(node->key_value), value2);
	if (!new_value)
		perror_exit("Malloc failed\n");
	replace_node_value(node, new_value);
	free(new_value);
}

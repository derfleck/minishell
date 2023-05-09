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

t_env	*find_env_node(t_env **env, char *key)
{
	t_env	*node;

	if (env == NULL)
		return (NULL);
	node = *env;
	while (node && ft_strncmp(node->key_value, key, ft_strlen(key)))
		node = node->next;
	return (node);
}

t_env	*replace_node(t_env *node, char *new_value)
{
	char	*key;

	if (node == NULL)
		return (NULL);
	key = ft_strjoin(split_env_key(node->key_value), "=");
	if (!key)
		perror("Malloc failed");
	node->key_value = free_ptr(node->key_value);
	node->key_value = ft_strjoin(key, new_value);
	if (node->key_value == NULL)
		perror("Malloc failed");
	free(key);
	return (node);
}

void	*free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

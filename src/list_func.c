#include "../inc/minishell.h"

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

	printf("%s\n", key);
	if (env == NULL)
		return (NULL);
	node = *env;
	while (node && ft_strncmp(node->key_value, key, ft_strlen(key)))
		node = node->next;
	return (node);
}

t_env	*replace_node(t_env *node, char *new_value)
{
	if (node == NULL)
		return (NULL);
	node->key_value = free_ptr(node->key_value);
	node->key_value = ft_strdup(new_value);
	return (node);
}

void	*free_env_node(t_env *node)
{
	if (node == NULL)
		return (NULL);
	node->key_value = free_ptr(node->key_value);
	node = free_ptr(node);
	return (NULL);
}

void	*free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

char	*split_env_value(char *str)
{
	if (!str)
		return (NULL);
	while (*str != '=')
		str++;
	str++;
	return (str);
}

char	*split_env_key(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '=')
		i++;
	ptr = &str[i];
	str[i] = '\0';
	return (str);
}

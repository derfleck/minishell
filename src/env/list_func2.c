#include "../../inc/minishell.h"

void	add_node_to_list(t_env **head, t_env *node)
{
	t_env	*temp;

	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node;
	node->next = NULL;
}

void	remove_node(t_env **head, char *key)
{
	t_env	*temp;
	t_env	*prev;

	if (head == NULL || !key)
		return ;
	prev = NULL;
	temp = *head;
	while (ft_strncmp(key, split_env_key(temp->key_value), ft_strlen(key)))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	if (prev == NULL)	//update head?
		*head = temp->next;
	else
		prev->next = temp->next;
	free_ptr(temp->key_value);
	free_ptr(temp);
}

char	*split_env_value(char *str)
{
	if (!str)
		return (NULL);
	while (*str != '=' && str)
		str++;
	str++;
	if (!str)
		return (NULL);
	return (str);
}

char	*split_env_key(const char *str)
{
	size_t		i;
	char		*key;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '=' && str)
		i++;
	key = ft_substr(str, 0, i);
	if (!key)
		perror("Malloc failed");
	return (key);
}
//TODO free key somewhere!!!
//or alternatively a no-malloc option:
// char	*split_env_key(const char *str)
// {
// 	size_t			i;
// 	static char		key[250];

// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	while (str[i] != '=' && str)
// 		i++;
// 	ft_memmove(key, str, i);
// 	key[(int)i] = '\0';
// 	return (key);
// }

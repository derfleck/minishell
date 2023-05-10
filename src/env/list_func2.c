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
/* removes node - used for builtin UNSET 
TODO: if head id removed, I get a segfault!!!! */
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
	if (prev == NULL)
		*head = (*head)->next; //segfaults if env is called after
	else
		prev->next = temp->next;
	free_ptr(temp->key_value);
	free_ptr(temp);
}

int	key_validity_check(char *key)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(key) - 1;
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			if (i == len && key[i] == '+')
				return (-1);
			else
				return (0);
		}
	}
	return (1);
}
/* Allow only alphanumericals and the '_' in the key received. If true, it returns 1. If 
false, it returns 0. If the last element before the null is +, returns -1 (important for export) */

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
		perror_exit("Malloc failed\n");
	if (!key_validity_check(key))
	{
		printf("Minishell: export: %s: not a valid identifier\n", key);
		return (NULL);
	}	
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

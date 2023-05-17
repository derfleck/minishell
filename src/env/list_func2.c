#include "../../inc/minishell.h"

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
		(*head) = (*head)->next;
	else
		prev->next = temp->next;
	free_ptr(temp->key_value);
	free_ptr(temp);
}

/* Allow only alphanumericals and the '_' in the key received.
If true, it returns 1. If false, it returns 0.
If the last element before the null is +, returns -1 (important for export) */
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

/* receives key=value string, splits the value off (everything after
the (=) sign, and returns it as a str.
If something goes wrong, returns a NULL */
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

/* receives key=value string, splits the key off (everything before
the (=) sign, and returns it as an allocated new str
TODO: free key somewhere!!! */
char	*split_env_key(const char *str)
{
	size_t		i;
	char		*key;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
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
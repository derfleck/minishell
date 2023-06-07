#include "../../inc/minishell.h"

/* Returns the keyword that is after the ($) -> at position i
and before the next space character or end of string */
char	*return_key(char *str)
{
	char	*key;
	int		len;

	if (!str)
		return (NULL);
	len = return_key_len(str);
	if (!len)
		return (NULL);
	key = malloc (sizeof (char) * (len + 1));
	if (!key)
		perror_exit("MALLOC failed\n");
	ft_memmove(key, str, len);
	key[len] = '\0';
	return (key);
}

/* Gets pointer at start of keyword, counts length of key only */
int	return_key_len(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	if (ft_isnum(str[0]) || (!ft_isalnum(str[0]) && str[0] != '_'))
		return (1);
	while (ft_isalnum(str[len]) || str[len] == '_' || \
	str[len] == '(' || str[len] == ')')
		len++;
	return (len);
}

// /* Returns length of value from key_value string 
// Currently not used */
// int	return_value_len(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i++])
// 	{
// 		if (str[i] == '=')
// 		{
// 			i++;
// 			while (str[i++])
// 				j++;
// 		}
// 	}
// 	return (j);
// }

/* Check if string after dollarsign is a valid env var and
returns the value if found. Returns NULL if not found or no key  */
char	*check_key_exist(t_env *head, char *i)
{	
	char	*key;
	t_env	*node;

	key = return_key(i);
	if (!key || ft_isnum(key[0]))
		return (NULL);
	node = find_env_node(head, key);
	if (!node)
	{
		free (key);
		return (NULL);
	}
	free (key);
	return (split_env_value(node->key_value));
}

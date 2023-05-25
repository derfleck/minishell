#include "../../inc/minishell.h"

/* Returns the keyword that is after the ($) -> at position i
and before the next space character or end of string */
char	*return_key(char *str)
{
	char	*ptr;
	int		len;

	if (!str)
		return (NULL);
	len = return_key_len(str);
	if (!len)
		return (NULL);
	ptr = malloc (sizeof (char) * (len + 1));
	if (!ptr)
		perror_exit("MALLOC failed\n");
	ft_memmove(ptr, str, len);
	ptr[len] = '\0';
	return (ptr);
}

/* Gets pointer at start of keyword, counts length of key only */
int	return_key_len(char *str)
{
	int	len;

	len = 0;
	while (ft_isalnum(str[len]) || str[len] == '_' || \
	str[len] == '(' || str[len] == ')')
		len++;
	return (len);
}

/* Returns length of value from key_value string */
int	return_value_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i++])
	{
		if (str[i] == '=')
		{
			i++;
			while (str[i++])
				j++;
		}
	}
	return (j);
}

/* Check if string after dollarsign is a valid env var and
returns the value if found. Returns NULL if not found or no key  */
char	*check_key_exist(t_env **head, char *i)
{	
	char	*key;
	t_env	*node;

	key = return_key(i);
	if (!key)
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

/* returns newly allocated string after expanding */
char	*expand_env_var(char *input, char *dollar, char *value)
{
	char	*pre;
	char	*post;
	char	*new_str;
	int		key_len;

	pre = return_pre_str(input, dollar);
	if (!pre)
		new_str = ft_strdup(value);
	else
		new_str = ft_strjoin(pre, value);
	if (!new_str)
		perror_exit("Malloc failed\n");
	free(pre);
	key_len = return_key_len(dollar + 1);
	post = return_post_str(dollar + key_len);
	if (!post)
		return (new_str);
	new_str = ft_strjoin(new_str, post);
	if (!new_str)
		perror_exit("Malloc failed\n");
	free(post);
	return (new_str);
}

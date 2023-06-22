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
		perror_exit("Malloc failed\n");
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
	{
		if (str[0] == '/')
			return (0);
		else
			return (1);
	}
	while (ft_isalnum(str[len]) || str[len] == '_' || \
	str[len] == '(' || str[len] == ')')
		len++;
	return (len);
}

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

/* gets input and pointer to dollarsign (speci),
returns newly allocated pre-str that is from 
the 0th element until (excluding) spec  */
char	*return_pre_str(char *input, char *speci)
{
	char	*pre;
	int		i;

	i = 0;
	while (input[i] && input + i != speci)
		i++;
	if (i == 0)
		return (NULL);
	pre = ft_substr(input, 0, (size_t)i);
	if (!pre)
		perror_exit("Malloc_failed\n");
	return (pre);
}

/* gets pointer to dollarsign + keylength (last char of the key),
returns newly allocated str that is from end of key + 1 to endofstring */
char	*return_post_str(char *key_end)
{
	char	*post;
	int		len;

	len = 0;
	while (key_end[len])
		len++;
	if (len == 0)
		return (ft_strdup(""));
	post = ft_substr(key_end, 1, len);
	if (post[0] == '?' && key_end[0] == '$')
		post++;
	if (!post)
		perror_exit("Malloc_failed\n");
	return (post);
}

#include "../../inc/minishell.h"

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
		return ("");
	post = ft_substr(key_end, 1, len);
	if (!post)
		perror_exit("Malloc_failed\n");
	return (post);
}

/* Creates new HOME env node in case HOME was unset. */
t_env	*create_home(char *str, t_env *head)
{
	t_env	*node;

	node = create_node(str);
	add_node_to_list(head, node);
	return (node);
}

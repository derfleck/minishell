#include "../../inc/minishell.h"

/* Gets everything to recreate new, expanded string.
Spec is either ($) or (~) 
choses what to do of the following 3 functions:
 - expand_home
 - expand_env_var
 - remove_var_reference  */
char	*replace_string(char *input, t_env *head, char *spec)
{
	char	*value;
	char	*new_str;

	if ((input[0] == '~' && input[1] == '\0') || \
	(input[0] == '~' && input[1] == '/'))
		return (expand_home(input, head, spec));
	if (spec[0] == '$')
	{
		value = check_key_exist(head, spec + 1);
		if (!value)
		{
			new_str = ft_strdup(input);
			if (spec[1] == '?')
				new_str = expand_status(input, spec);
			return (new_str);
		}
		else
			new_str = expand_env_var(input, spec, value);
		return (new_str);
	}
	return (input);
}

/* tilde position arrives as char*. Replace it with value of home. 
rejoin str together. Return new str */
char	*expand_home(char *input, t_env *head, char *tilde)
{
	char	*home_value;
	char	*new_str;
	t_env	*node;
	char	*pre;
	char	*post;

	node = find_env_node(head, "HOME");
	if (!node)
		node = create_home("HOME=/nfs/homes/", &head);
	home_value = split_env_value(node->key_value);
	pre = return_pre_str(input, tilde);
	if (!pre)
		new_str = ft_strdup(home_value);
	else
		new_str = ft_strjoin(pre, home_value);
	if (!new_str)
		perror_exit("Malloc failed\n");
	post = return_post_str(tilde + return_key_len(tilde + 1));
	new_str = ft_strjoin(new_str, post);
	if (!new_str)
		perror_exit("Malloc failed\n");
	free_ptr(pre);
	free_ptr(post);
	return (new_str);
}

/* Receives input and dollarsign position as char* 
object: excise dollarsign and key, replace with empty str ("") */
char	*remove_var_reference(char *input, char *dollar)
{
	char	*new_str;
	char	*pre;
	char	*post;
	int		key_len;

	pre = return_pre_str(input, dollar);
	if (!pre)
		new_str = ft_strdup("");
	else
		new_str = ft_strjoin(pre, "");
	if (!new_str)
		perror_exit("Malloc failed\n");
	free_ptr(pre);
	key_len = return_key_len(dollar + 1);
	post = return_post_str(dollar + key_len);
	if (!post)
		return (new_str);
	new_str = ft_strjoin(new_str, post);
	if (!new_str)
		perror_exit("Malloc failed\n");
	free_ptr(post);
	return (new_str);
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
	free_ptr(pre);
	key_len = return_key_len(dollar + 1);
	post = return_post_str(dollar + key_len);
	if (!post)
		return (new_str);
	new_str = ft_strjoin(new_str, post);
	if (!new_str)
		perror_exit("Malloc failed\n");
	free_ptr(post);
	return (new_str);
}

/* Creates new HOME env node in case HOME was unset. */
t_env	*create_home(char *str, t_env **head)
{
	t_env	*node;

	node = create_node(str, *head);
	add_node_to_list(head, node);
	node->next = NULL;
	return (node);
}

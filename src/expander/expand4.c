#include "../../inc/minishell.h"

/* Gets everything to recreate new, expanded string.
Spec is either ($) or (~) 
choses what to do out of the following 3 functions:
 - expand_home (if ~)
 - expand status (if $?)
 - expand_env_var (if $ ) */
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
			if (spec[1] == '?')
				new_str = expand_status(input, spec, head);
			else
				new_str = remove_var_reference(input, spec, head);
			return (new_str);
		}
		else
			new_str = expand_env_var(input, spec, value, head);
		return (new_str);
	}
	return (ft_strdup(input));
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
	home_value = ft_strdup(split_env_value(node->key_value));
	if (!home_value)
		perror_exit_free_env("Malloc_failed\n", head);
	pre = return_pre_str(input, tilde, head);
	new_str = safe_join(pre, home_value, head);
	if (!new_str)
		perror_exit_free_env("Malloc_failed\n", head);
	post = return_post_str(tilde + return_key_len(tilde + 1), head);
	new_str = safe_join(new_str, post, head);
	if (!new_str)
		perror_exit_free_env("Malloc_failed\n", head);
	return (new_str);
}

/* Receives input and dollarsign position as char* 
object: excise dollarsign and key, replace with empty str ("") */
char	*remove_var_reference(char *input, char *dollar, t_env *head)
{
	char	*new_str;
	char	*new_str2;
	char	*pre;
	char	*post;
	int		key_len;

	pre = return_pre_str(input, dollar, head);
	new_str = ft_strdup(pre);
	free_ptr(pre);
	if (!new_str)
		perror_exit_free_env("Malloc_failed\n", head);
	key_len = return_key_len(dollar + 1);
	post = return_post_str(dollar + key_len, head);
	new_str2 = safe_join(new_str, post, head);
	if (!new_str2)
		perror_exit_free_env("Malloc_failed\n", head);
	return (new_str2);
}

/* returns newly allocated string after expanding */
char	*expand_env_var(char *input, char *dollar, char *value, t_env *head)
{
	char	*pre;
	char	*post;
	char	*new_str;
	int		key_len;

	pre = return_pre_str(input, dollar, head);
	new_str = safe_join(pre, value, head);
	if (!new_str)
		perror_exit_free_env("Malloc_failed\n", head);
	key_len = return_key_len(dollar + 1);
	post = return_post_str(dollar + key_len, head);
	new_str = safe_join(new_str, post, head);
	if (!new_str)
		perror_exit_free_env("Malloc_failed\n", head);
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

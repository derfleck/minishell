#include "../../inc/minishell.h"

/* Makes sure expander can handle all incoming strings */
char	**expander_start(char **args, t_env **head)
{
	int	i;

	i = 0;
	if (!args)
		return (NULL);
	while (args[i])
	{
		args[i] = expander(args[i], head);
		i++;
	}
	return (args);
}

char	*expander(char *input, t_env **head)
{
	int	i;

	i = -1;
	if (!input || !head)
		return (NULL);
	if (input[0] == '\'')
		return (ft_strtrim(input, "'"));
	else
	{
		if (input[0] == '"' && input[1] != '~')
			input = ft_strtrim(input, "\"");
		while (input[++i])
		{
			if (input[i] == '$' || input[i] == '~')
			{
				input = replace_string(input, head, &input[i]);
				if (input[i] == '~')
					return (input);
				i = -1;
			}
		}
	}
	return (input);
}

/* Gets everything to recreate new, expanded string.
TODO: to Malloc new, expanded string */
char	*replace_string(char *input, t_env **head, char *spec)
{
	char	*value;
	char	*new_str;

	if ((input[0] == '~' && input[1] == '\0') || \
	(input[0] == '~' && input[1] == '/'))
		return (expand_home(input, head, spec));
	else if (input[0] == '"' && input[1] == '~')
		return (ft_strtrim(input, "\""));
	if (spec[0] == '$')
	{
		value = check_key_exist(head, spec + 1);
		if (!value)
		{
			new_str = remove_var_reference(input, spec);
			return (new_str);
		}
		else
			new_str = expand_env_var(input, spec, value);
		return (new_str);
	}
	return (input);
}

/* i is position of tilde. Replace it with value of home. rejoin str 
Return new str */
char	*expand_home(char *input, t_env **head, char *tilde)
{
	char	*home_value;
	char	*new_str;
	t_env	*node;
	char	*pre;
	char	*post;

	node = find_env_node(head, "HOME");
	if (!node)
		node = create_home("HOME=/nfs/homes/", head);
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
	free(pre);
	free(post);
	return (new_str);
}

/* Receives input and place of dollarsign, 
object: excise dollarsign and key, replace with "" */
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

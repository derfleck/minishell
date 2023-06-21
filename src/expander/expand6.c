#include "../../inc/minishell.h"

int	check_invalid_follow(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			return (1);
	}
	return (0);
}

char	*remove_dollarsign_bef_quotes(char *str)
{
	char	*new;

	if (!str)
		return (NULL);
	new = ft_strdup(&str[1]);
	return (new);
}

char	*expand_status(char *input, char *dollar)
{
	char	*new_str;
	char	*pre;
	char	*post;
	char	*status;

	status = ft_itoa(g_stat);
	if (!status)
		perror_exit("Malloc failed\n");
	pre = return_pre_str(input, dollar);
	if (!pre)
		new_str = ft_strdup(status);
	else
		new_str = ft_strjoin(pre, status);
	free_ptr(pre);
	free_ptr(status);
	if (!new_str)
		perror_exit("Malloc failed\n");
	post = return_post_str(dollar + 1);
	if (!post)
		return (new_str);
	new_str = ft_strjoin(new_str, post);
	if (!new_str)
		perror_exit("Malloc failed\n");
	free_ptr(post);
	return (new_str);
}

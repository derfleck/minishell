#include "../../inc/minishell.h"

/* Pre - checks if there's need at all for expansion
Returns 1 if expansion is needed. 0 if not */
int	need_to_expand(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '$' || (input[i] == '~' && (input[i + 1] == '\0' || \
		input[i + 1] == '/')))
			return (1);
	}
	return (0);
}

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

char	*remove_dollarsign_bef_quotes(char *str, t_env *head)
{
	char	*new;

	if (!str)
		return (NULL);
	new = ft_strdup(&str[1]);
	if (!new)
		perror_exit_free_env("Malloc failed\n", head);
	return (new);
}

char	*expand_status(char *input, char *dollar, t_env *head)
{
	char	*new_str;
	char	*new_str2;
	char	*pre;
	char	*post;
	char	*status;

	status = ft_itoa(g_stat);
	if (!status)
		perror_exit_free_env("Malloc failed\n", head);
	pre = return_pre_str(input, dollar, head);
	new_str = safe_join(pre, status, head);
	if (!new_str)
		perror_exit_free_env("Malloc failed\n", head);
	post = return_post_str(dollar + 1, head);
	new_str2 = safe_join(new_str, post, head);
	if (!new_str2)
		perror_exit_free_env("Malloc failed\n", head);
	return (new_str2);
}

int	count_dollars(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$')
			count++;
	}
	return (count);
}

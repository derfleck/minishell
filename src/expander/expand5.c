/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:13:26 by rmocsai           #+#    #+#             */
/*   Updated: 2023/06/26 15:37:39 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* checks if Dollar is followed by quote (bash behaves differently) */
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
	char	*pre;
	char	*post;
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			break ;
	}
	pre = return_pre_str(str, &str[i], head);
	post = return_post_str(&str[i], head);
	new = safe_join(pre, post, head);
	if (!new)
		perror_exit_free_env("Malloc failed\n", head);
	return (new);
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

/* joins together any size of char arrays into one str */
char	*ft_strjoin_multiple(char **arr, t_env *head)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	str = ft_strdup(arr[0]);
	if (!str)
		perror_exit_free_env("Malloc_failed\n", head);
	while (arr[++i])
	{
		tmp = str;
		str = ft_strjoin(str, arr[i]);
		if (!str)
			perror_exit_free_env("Malloc_failed\n", head);
		tmp = free_ptr(tmp);
	}
	return (str);
}

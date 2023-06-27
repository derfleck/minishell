/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:13:06 by rmocsai           #+#    #+#             */
/*   Updated: 2023/06/27 14:54:18 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Starts from right after the first quote (start + 1)
and returns an int representing the length of str until the end quote */
static int	return_quote_len(char *start, char c)
{
	int	i;

	i = 0;
	while (start[++i])
	{
		if (start[i] == c)
			break ;
	}
	return (i);
}

/* Creates new string with the content of the quotes without quotes
DON'T FREE INPUT */
static char	*create_quote_free_str(char *input, int start, int end, t_env *head)
{
	char	*new;
	char	*quoted_str;
	char	quote_type[2];
	char	c;

	c = input[start];
	quote_type[0] = c;
	quote_type[1] = '\0';
	quoted_str = ft_substr(input, start, (size_t)end - start + 1);
	if (!quoted_str)
		perror_exit_free_env("Malloc_failed\n", head);
	new = ft_strtrim(quoted_str, quote_type);
	if (!new)
		perror_exit_free_env("Malloc_failed\n", head);
	quoted_str = free_ptr(quoted_str);
	return (new);
}

/* Removes quotes (at positions start and end) from an incoming string,
 sends new string back
 SHOULD free input! */
static char	*remove_quotes(char *input, int start, int end, t_env *head)
{
	char	*new;
	char	*pre;
	char	*post;
	char	*str;

	pre = return_pre_str(input, &input[start], head);
	str = create_quote_free_str(input, start, end, head);
	new = safe_join(pre, str, head);
	if (!new)
		perror_exit_free_env("Malloc_failed\n", head);
	post = return_post_str(&input[end], head);
	new = safe_join(new, post, head);
	if (!new)
		perror_exit_free_env("Malloc_failed\n", head);
	input = free_ptr(input);
	return (new);
}

/* as it says - removes all outside quote pairs from given str */
char	*kill_quotes(char *expanded, t_env *head)
{
	char	*str;
	int		i;
	int		j;
	int		end;

	i = 0;
	j = 0;
	str = ft_strdup(expanded);
	if (!str)
		perror_exit_free_env("Malloc_failed\n", head);
	while (expanded[i])
	{
		if (expanded[i] == '"' || expanded[i] == '\'')
		{
			end = return_quote_len(&expanded[i], expanded[i]);
			str = remove_quotes(str, j, j + end, head);
			i = i + end;
			j = j + end - 2;
		}
		i++;
		j++;
	}
	return (str);
}

int	check_simple_input(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (!ft_isalnum(str[i + 1]) && str[i + 1] != '?' && \
			str[i + 1] != '_')
				return (1);
		}
	}
	return (0);
}

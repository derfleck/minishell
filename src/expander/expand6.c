/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:37:30 by rmocsai           #+#    #+#             */
/*   Updated: 2023/06/26 15:37:39 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**split_by_quotes(char *input, t_env *head)
{
	char	**arr;
	char	s;
	int		count;

	s = '!';
	count = ft_count_elements(input, s);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		perror_exit_free_env("Malloc_failed\n", head);
	arr = ft_quotesplitter(arr, input, count, head);

	return (arr);
}

/* Counts how many strings need to be allocated */
int	ft_count_elements(char *input, char s)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] && (input[i] == '\'' || input[i] == '"'))
		{
			count++;
			s = input[i];
			i++;
			while (input[i] != s)
				i++;
		}
		else if (input[i])
		{
			count++;
			while (input[i] && (input[i] != '"' && input[i] != '\''))
				i++;
			i--;
		}
	}
	return (count);
}

static int	quotesplitter1(char *input, int *i)
{
	int	len;

	len = 0;
	while (input[*i] && input[*i] != '"' && input[*i] != '\'')
	{
		(*i)++;
		len++;
	}
	return (len);
}

static int	quotesplitter2(char *input, int *i)
{
	char	q;
	int		len;

	q = input[*i];
	(*i)++;
	len = 2;
	while (input[*i] != q)
	{
		(*i)++;
		len++;
	}
	(*i)++;
	return (len);
}

/* Gets input, tries to split it to **arr according to:
characters not enclosed in quotes, quoted blocks bordered by
single quotes, and quoted blocks bordered by double quotes. */
char	**ft_quotesplitter(char **arr, char *input, int count, t_env *head)
{
	int		i;
	int		len;
	int		element;

	i = 0;
	element = -1;
	while (++element < count)
	{
		if (input[i] && (input[i] != '"' && input[i] != '\''))
			len = quotesplitter1(input, &i);
		else if (input[i] && (input[i] == '"' || input[i] == '\''))
			len = quotesplitter2(input, &i);
		arr[element] = ft_substr(input, i - len, len);
		if (!arr[element])
			perror_exit_free_env("Malloc_failed\n", head);
	}
	arr[element] = NULL;
	return (arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:34:25 by rmocsai           #+#    #+#             */
/*   Updated: 2023/06/29 12:34:55 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**split_by_dollars(char *input, t_env *head)
{
	char	**arr;
	int		l;
	char	*trim;

	trim = ft_strtrim(input, "\"");
	if (!trim)
		perror_exit_free_env("Malloc_failed\n", head);
	arr = ft_split(trim, '$');
	if (!arr)
		perror_exit_free_env("Malloc_failed\n", head);
	l = -1;
	while (arr[++l])
	{
		if ((l == 0 && trim[0] == '$') || l)
			arr[l] = safe_join(ft_strdup("$"), arr[l], head);
		if (!arr[l])
			perror_exit_free_env("Malloc_failed\n", head);
	}
	trim = free_ptr(trim);
	arr[l] = NULL;
	return (arr);
}

/* Checks incoming str if expansion is needed, also if multiple  */
char	*do_expansion_pre(char *input, t_env *head)
{
	int		i;
	int		j;
	char	**arr;
	char	*new_str;

	arr = NULL;
	i = count_dollars(input);
	if (i < 1 && input[0] != '~')
		return (ft_strdup(input));
	else if (i > 1)
	{
		j = -1;
		if (check_simple_input(input))
			return (do_expansion(input, head));
		arr = split_by_dollars(input, head);
		if (!arr[0])
			return (do_expansion(input, head));
		while (arr[++j])
			arr[j] = do_expansion_with_freeing(arr[j], head);
		new_str = ft_strjoin_multiple(arr, head);
	}
	else
		new_str = do_expansion(input, head);
	arr = free_charray(arr);
	return (new_str);
}

/* Prepares input str for expansion */
char	*do_expansion(char *input, t_env *head)
{
	int		i;
	char	*new_str;

	i = -1;
	while (input[++i])
	{
		if ((input[i] == '$' && (ft_isalnum(input[i + 1]) || \
		input[i + 1] == '_' || input[i + 1] == '?')) || input[i] == '~')
		{
			new_str = replace_string(input, head, &input[i]);
			if (!new_str)
				perror_exit_free_env("Malloc_failed\n", head);
			return (new_str);
		}
	}
	return (ft_strdup(input));
}

/* Prepares input str for expansion - frees input*/
char	*do_expansion_pre_with_freeing(char *input, t_env *head)
{
	int		i;
	int		j;
	char	**arr;
	char	*new_str;

	arr = NULL;
	i = count_dollars(input);
	if (i < 1 && input[0] != '~')
		return (input);
	else if (i > 1)
	{
		j = -1;
		if (check_simple_input(input))
			return (do_expansion_with_freeing(input, head));
		arr = split_by_dollars(input, head);
		while (arr[++j])
			arr[j] = do_expansion_with_freeing(arr[j], head);
		new_str = ft_strjoin_multiple(arr, head);
		arr = free_charray(arr);
	}
	else
		return (do_expansion_with_freeing(input, head));
	input = free_ptr(input);
	return (new_str);
}

/* Checks incoming str if expansion is needed
 - but this time it frees the input */
char	*do_expansion_with_freeing(char *input, t_env *head)
{
	int		i;
	char	*new_str;

	i = -1;
	while (input[++i])
	{
		if ((input[i] == '$' && (ft_isalnum(input[i + 1]) || \
		input[i + 1] == '_' || input[i + 1] == '?')) || input[i] == '~')
		{
			new_str = replace_string(input, head, &input[i]);
			if (!new_str)
				perror_exit_free_env("Malloc_failed\n", head);
			input = free_ptr(input);
			return (new_str);
		}
	}
	return (input);
}

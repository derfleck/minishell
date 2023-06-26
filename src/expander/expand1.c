/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:37:14 by rmocsai           #+#    #+#             */
/*   Updated: 2023/06/26 15:37:35 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Makes sure expander can handle all incoming strings
void	expander_start(t_lexer *lex, t_env *head)
{
	t_lexer	*lex_tmp;
	char	*temp;

	lex_tmp = lex;
	while (lex_tmp)
	{
		if (lex_tmp->token == LESS_LESS && lex_tmp->next)
		{
			lex_tmp = lex_tmp->next->next;
			continue ;
		}
		else if (lex_tmp->token)
			lex_tmp = lex_tmp->next;
		if (lex_tmp)
		{
			temp = lex_tmp->str;
			lex_tmp->str = expander(lex_tmp->str, head);
			temp = free_ptr(temp);
			lex_tmp = lex_tmp->next;
		}
	}
}

/* Iterates through the str, if finds a quotation mark, 
returns 1 if not, returns 0 */
static int	found_quotes(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
			return (1);
	}
	return (0);
}

/* deals with each incoming arg from expander_start one by one */
char	*expander(char *input, t_env *head)
{
	char	*new;
	char	*new2;

	new = NULL;
	if (!input)
		return (NULL);
	if (found_quotes(input))
	{
		new = deal_with_expansion(input, head);
		if (!new)
			perror_exit_free_env("Malloc failed\n", head);
		new2 = kill_quotes(new, head);
		new = free_ptr(new);
		return (new2);
	}
	else
		new = do_expansion_pre(input, head);
	return (new);
}

/* Pre - checks if there's need at all for expansion
Returns 1 if expansion is needed. 0 if not */
static int	need_to_expand(char *input)
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

/* gets string with surely a quote in it.
iterates through it to find first occurence.
if single: just continues.
if double: sends inner str for expansion check.
Then continues */
char	*deal_with_expansion(char *input, t_env *head)
{
	int		i;
	char	**arr;
	char	*str;

	i = -1;
	if (!need_to_expand(input))
		return (ft_strdup(input));
	if (check_invalid_follow(input))
	{
		str = remove_dollarsign_bef_quotes(input, head);
		arr = split_by_quotes(str, head);
		str = free_ptr(str);
	}
	else
		arr = split_by_quotes(input, head);
	while (arr[++i])
	{
		if (arr[i][0] != '\'')
			arr[i] = do_expansion_pre_with_freeing(arr[i], head);
	}
	str = ft_strjoin_multiple(arr, head);
	if (!str)
		perror_exit_free_env("Malloc failed\n", head);
	arr = free_charray(arr);
	return (str);
}

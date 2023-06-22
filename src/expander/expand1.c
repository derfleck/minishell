#include "../../inc/minishell.h"

//Makes sure expander can handle all incoming strings
void	expander_start(t_lexer *lex, t_env *head)
{
	t_lexer	*lex_tmp;

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
			lex_tmp->str = expander(lex_tmp->str, head);
			lex_tmp = lex_tmp->next;
		}
	}
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
		free_ptr(new);
		return (new2);
	}
	else
		new = do_expansion_pre(input, head);
	return (new);
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

	(void)head;
	i = -1;
	if (!need_to_expand(input))
		return (input);
	if (check_invalid_follow(input))
	{
		str = remove_dollarsign_bef_quotes(input, head);
		return (str);
	}
	arr = split_by_quotes(input, head);
	while (arr[++i])
	{
		if (arr[i][0] != '\'')
			arr[i] = do_expansion_pre_with_freeing(arr[i], head);
	}
	str = ft_strjoin_multiple(arr, head);
	if (!str)
		perror_exit_free_env("Malloc failed\n", head);
	free_charray(arr);
	return (str);
}

/* Checks incoming str if expansion is needed 
REMOVE VAR REF here? 
Multiple $s in one str? */
char	*do_expansion_pre(char *input, t_env *head)
{
	int		i;
	int		j;
	char	**arr;
	char	*new_str;

	i = count_dollars(input);
	if (i < 1)
		return (ft_strdup(input));
	else if (i > 1)
	{
		j = -1;
		arr = split_by_dollars(input, head, i);
		while (arr[++j])
			arr[j] = do_expansion_with_freeing(arr[j], head);
		new_str = ft_strjoin_multiple(arr, head);
	}
	else
		new_str = do_expansion(input, head);
	return (new_str);
}

/* Checks incoming str if expansion is needed 
REMOVE VAR REF here? 
Multiple $s in one str? */
char	*do_expansion_pre_with_freeing(char *input, t_env *head)
{
	int		i;
	int		j;
	char	**arr;
	char	*new_str;

	i = count_dollars(input);
	if (i < 1)
		return (ft_strdup(input));
	else if (i > 1)
	{
		j = -1;
		arr = split_by_dollars(input, head, i);
		while (arr[++j])
			arr[j] = do_expansion_with_freeing(arr[j], head);
		new_str = ft_strjoin_multiple(arr, head);
	}
	else
		new_str = do_expansion(input, head);
	free_ptr(input);
	return (new_str);
}

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
			free (input);
			return (new_str);
		}
	}
	return (input);
}

char	**split_by_dollars(char *input, t_env *head, int i)
{
	char	**arr;
	int		l;

	arr = malloc (sizeof (char *) * (i + 1));
	if (!arr)
		perror_exit_free_env("Malloc_failed\n", head);
	arr = ft_split(input, '$');
	if (!arr)
		perror_exit_free_env("Malloc_failed\n", head);
	l = -1;
	while (++l < i)
	{
		arr[l] = ft_strjoin("$", arr[l]);
		if (!arr[l])
			perror_exit_free_env("Malloc_failed\n", head);
	}
	arr[l] = NULL;
	return (arr);
}

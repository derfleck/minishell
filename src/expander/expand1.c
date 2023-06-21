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

	if (!input)
		return (NULL);
	if (found_quotes(input))
	{
		new = deal_with_expansion(input, head);
		new = kill_quotes(new);
	}
	else
		new = do_expansion(input, head);
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

	(void)head;
	i = -1;
	if (!need_to_expand(input))
		return (input);
	if (check_invalid_follow(input))
	{
		input = remove_dollarsign_bef_quotes(input);
		return (input);
	}
	arr = split_by_quotes(input, head);
	while (arr[++i])
	{
		if (arr[i][0] != '\'')
			arr[i] = do_expansion(arr[i], head);
	}	
	input = ft_strjoin_multiple(arr);
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (input);
}

/* Checks incoming str if expansion is needed */
char	*do_expansion(char *input, t_env *head)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if ((input[i] == '$' && (ft_isalnum(input[i + 1]) || \
		input[i + 1] == '_' || input[i + 1] == '?')) || input[i] == '~')
			input = replace_string(input, head, &input[i]);
	}
	return (input);
}

char	**split_by_quotes(char *input, t_env *head)
{
	char	**arr;
	char	s;
	int		count;

	(void)head;
	s = '!';
	count = ft_count_elements(input, s);
	arr = malloc (sizeof(char *) * (count + 1));
	if (!arr)
		perror_exit("Malloc failed\n");
	arr = ft_quotesplitter(arr, input, count);
	return (arr);
}

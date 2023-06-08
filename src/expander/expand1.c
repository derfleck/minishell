#include "../../inc/minishell.h"

/* Makes sure expander can handle all incoming strings */
char	**expander_start(char **args, t_env *head)
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
	free (input);
	return (arr);
}

/* Gets input, tries to split it to **arr according to:
characters not enclosed in quotes, quoted blocks bordered by
single quotes, and quoted blocks bordered by double quotes. */
char	**ft_quotesplitter(char **arr, char *input, int count)
{
	int		i;
	int		len;
	int		element;
	char	q;

	i = 0;
	element = -1;
	while (++element < count)
	{
		len = 0;
		if (input[i] && (input[i] != '"' && input[i] != '\''))
		{
			while (input[i] && input[i] != '"' && input[i] != '\'')
			{
				i++;
				len++;
			}
		}
		else if (input[i] && (input[i] == '"' || input[i] == '\''))
		{	
			q = input[i++];
			len = 2;
			while (input[i] != q)
			{
				i++;
				len++;
			}
			i++;
		}
		arr[element] = ft_substr(input, i - len, len);
	}
	arr[element] = NULL;
	return (arr);
}

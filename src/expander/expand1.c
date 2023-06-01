#include "../../inc/minishell.h"

//TODO: -if element after $sign is invalid for key, that should be excised and the rest kept. 
//TODO: echo 'jj'"o" invalid pointer!!! check this next

/* Makes sure expander can handle all incoming strings */
char	**expander_start(char **args, t_env **head)
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
char	*expander(char *input, t_env **head)
{
	char	*new;

	if (!input || !head)
		return (NULL);
	if (found_quotes(input))
		new = deal_with_quotes(input, head);
	else
		new = do_expansion(input, head);
	return (new);
}

/* gets string with surely a quote in it.
iterates through it to find first occurence.
if single - removes them and continues.
if double: removes them and sends inner str for expansion check.
Then continues */
char	*deal_with_quotes(char *input, t_env **head)
{
	int		i;
	int		end;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
		{
			end = i + return_quote_len(&input[i], input[i]);
			input = remove_quotes(input, i, end);
			i = end;
		}
		else if (input[i] == '"')
		{
			end = i + return_quote_len(&input[i], input[i]);
			input = remove_quotes(input, i, end);
			input = expand_parts(input, head, i, end - 2);
			//save the leftoverstr ?? then do it and return here? cause i is untrackable...
			i = end; //not true if expanded. TODO!
		}
		else if (input[i] == '$' || input[i] == '~')
			input = replace_string(input, head, &input[i]);
	}
	return (input);
}

/* Checks if expansion is needed for the quoted part of the strings. */
char	*expand_parts(char *input, t_env **head, int start, int end)
{
	int		i;

	(void)end;
	i = start - 1;
	while (input[++i])
	{
		if (input[i] == '$')
			input = replace_string(input, head, &input[i]);
	}
	return (input);
}

/* Removes quotes (at positions start and end) from an incoming string,
 sends new string back */
char	*remove_quotes(char *input, int start, int end)
{
	char	*new;
	char	*pre;
	char	*post;

	pre = return_pre_str(input, &input[start]);
	if (!pre)
		new = create_quote_free_str(input, start, end);
	else
		new = ft_strjoin(pre, create_quote_free_str(input, start, end));
	if (!new)
		perror_exit("Malloc failed\n");
	free(pre);
	post = return_post_str(&input[end]);
	new = ft_strjoin(new, post);
	if (!new)
		perror_exit("Malloc failed\n");
	free(input);
	free(post);
	return (new);
}

/* Creates new string with the content of the quotes without quotes */
char	*create_quote_free_str(char *input, int start, int end)
{
	char	*new;
	char	*quoted_str;

	quoted_str = ft_substr(input, start, (size_t)end - start + 1);
	if (!quoted_str)
		perror_exit("Malloc failed\n");
	new = ft_strtrim(quoted_str, "'\"");
	if (!new)
		perror_exit("Malloc failed\n");
	free(quoted_str);
	return (new);
}

/* Starts from right after the first quote (start + 1)
and returns an int representing the length of str until the end quote */
int	return_quote_len(char *start, char c)
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

/* Iterates through the str, if finds a quotation mark, 
returns 1 if not, returns 0 */
int	found_quotes(char *input)
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

/* Checks incoming str if expansion is needed  */
char	*do_expansion(char *input, t_env **head)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '$' || input[i] == '~')
		{
			input = replace_string(input, head, &input[i]);
			if (input[i] == '~')
				return (input); //YOU SURE? i++?
			i = -1; // what if tilde is kept?
		}
	}
	return (input);
}

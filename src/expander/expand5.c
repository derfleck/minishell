#include "../../inc/minishell.h"

/*  */
char	*kill_quotes(char *expanded)
{
	char	*str;
	int		i;
	int		j;
	int		end;

	i = 0;
	j = 0;
	str = ft_strdup(expanded);
	while (expanded[i])
	{
		if (expanded[i] == '"' || expanded[i] == '\'')
		{
			end = return_quote_len(&expanded[i], expanded[i]);
			str = remove_quotes(str, j, j + end, expanded[i]);
			i = i + end;
			j = j + end - 2;
		}
		i++;
		j++;
	}
	return (str);
}

/* Removes quotes (at positions start and end) from an incoming string,
 sends new string back */
char	*remove_quotes(char *input, int start, int end, char c)
{
	char	*new;
	char	*pre;
	char	*post;

	pre = return_pre_str(input, &input[start]);
	if (!pre)
		new = create_quote_free_str(input, start, end, c);
	else
		new = ft_strjoin(pre, create_quote_free_str(input, start, end, c));
	if (!new)
		perror_exit("Malloc failed\n");
	free(pre);
	post = return_post_str(&input[end]);
	if (post)
		new = ft_strjoin(new, post);
	if (!new)
		perror_exit("Malloc failed\n");
	free_ptr(post);
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

/* Creates new string with the content of the quotes without quotes */
char	*create_quote_free_str(char *input, int start, int end, char c)
{
	char	*new;
	char	*quoted_str;
	char	quote_type[2];

	quote_type[0] = c;
	quote_type[1] = '\0';
	quoted_str = ft_substr(input, start, (size_t)end - start + 1);
	if (!quoted_str)
		perror_exit("Malloc failed\n");
	new = ft_strtrim(quoted_str, quote_type);
	if (!new)
		perror_exit("Malloc failed\n");
	free_ptr(quoted_str);
	return (new);
}

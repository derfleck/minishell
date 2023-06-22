#include "../../inc/minishell.h"

char	**split_by_quotes(char *input, t_env *head)
{
	char	**arr;
	char	s;
	int		count;

	s = '!';
	count = ft_count_elements(input, s);
	arr = malloc (sizeof(char *) * (count + 1));
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

/* Gets input, tries to split it to **arr according to:
characters not enclosed in quotes, quoted blocks bordered by
single quotes, and quoted blocks bordered by double quotes. */
char	**ft_quotesplitter(char **arr, char *input, int count, t_env *head)
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
		if (!arr[element])
			perror_exit_free_env("Malloc_failed\n", head);
	}
	arr[element] = NULL;
	return (arr);
}

/* joins together any size of char arrays into one str */
char	*ft_strjoin_multiple(char **arr, t_env *head)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strjoin("", arr[0]);
	if (!str)
		perror_exit_free_env("Malloc_failed\n", head);
	while (arr[++i])
	{
		str = ft_strjoin(str, arr[i]);
		if (!str)
			perror_exit_free_env("Malloc_failed\n", head);
	}
	return (str);
}

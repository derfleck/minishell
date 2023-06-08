#include "../../inc/minishell.h"

/* Pre - checks if there's need at all for expansion
Returns 1 if expansion is needed. 0 if not */
int	need_to_expand(char *input)
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

/* Checks incoming str if expansion is needed  */
char	*do_expansion(char *input, t_env *head)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '$' || input[i] == '~')
		{
			input = replace_string(input, head, &input[i]);
			if (input[i] == '~')
				i++;
			else
				i = -1; //might get stuck!!!inf loop? just   i++?
		}
	}
	return (input);
}

/* joins together any size of char arrays into one str */
char	*ft_strjoin_multiple(char **arr)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strjoin("", arr[0]);
	if (!str)
		perror_exit("Malloc failed\n");
	while (arr[++i])
	{
		str = ft_strjoin(str, arr[i]);
		if (!str)
			perror_exit("Malloc failed\n");
	}
	return (str);
}

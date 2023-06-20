#include "../../inc/minishell.h"

//checks if character is token and moves index forward
static int	token_check(char *str, int *i)
{
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
	{
		if ((str[*i] == '<' || str[*i] == '>') && (str[*i] == str[*i + 1]))
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

//counts number of characters until separating character is found
//can be either one of the set characters, quotes or tokens
static int	get_sub(char *str, char *set)
{
	int	i;

	i = 0;
	while (ft_strchr(set, str[i]) == 0 && \
			(str[i] != '<' && str[i] != '>' && str[i] != '|'))
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quotes(str + i);
		else
			i++;
	}		
	return (i);
}

//counts number of elements including tokens
static int	cnt_with_token(char *str, char *set)
{
	int		i;
	int		nbr;
	char	*tmp;

	i = 0;
	nbr = 0;
	tmp = str;
	while (*tmp)
	{
		i = get_sub(tmp, set);
		if (i)
			nbr++;
		if (token_check(tmp, &i))
			nbr++;
		while (tmp[i] && (ft_strchr(set, tmp[i]) != 0 && \
				tmp[i] != '\'' && tmp[i] != '"'))
			i++;
		tmp += i;
	}
	return (nbr);
}

//empty 2D array after use/in case of error
void	empty_set(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i++]);
	}
	if (str)
		free(str);
}

//splits string based on character set
//keeps tokens for bash parsing (<, > and |)
char	**ft_split_set(char *str, char *set)
{
	char	**split;
	int		len;
	int		word;

	word = 0;
	split = ft_calloc(cnt_with_token(str, set) + 1, sizeof(char *));
	if (!split)
		return (empty_set(split), NULL);
	while (*str)
	{
		len = 0;
		if (token_check(str, &len))
			split[word++] = ft_substr(str, 0, len);
		str += len;
		len = get_sub(str, set);
		if (len)
			split[word++] = ft_substr(str, 0, len);
		while (str[len] && (ft_strchr(set, str[len]) != 0 && \
				str[len] != '\'' && str[len] != '"'))
			len++;
		str += len;
	}
	return (split);
}

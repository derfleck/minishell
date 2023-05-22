#include "../../inc/minishell.h"

//counts total number of commands in trimmed string
static int	cnt_cmd(char *str, char *set)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strtrim(str, set);
	j = 0;
	while (*tmp)
	{
		i = skip_quotes(tmp);
		while (ft_strchr(set, tmp[i]) == 0 && \
				(tmp[i] != '\'' || tmp[i] != '"'))
			i++;
		if (i)
			j++;
		while (ft_strchr(set, tmp[i]) != 0 && tmp[i])
			i++;
		tmp += i;
	}
	return (j);
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

/*
//helper, initializes int array with three int values
//0: start, 1: len, 3: overall position
static void	init_int_arr(int *i)
{
	int	num;

	num = 0;
	while (num < 3)
		i[num++] = 0;
}
*/

//splits string based if character in set is found
char	**ft_split_set(char *str, char *set)
{
	int		start;
	int		len;
	int		j;
	char	*tmp;
	char	**split;

	j = 0;
	start = 0;
	len = 0;
	tmp = ft_strtrim(str, set);
	split = ft_calloc(sizeof(char *), cnt_cmd(str, set) + 1);
	if (!split)
		empty_set(split);
	while (tmp[start])
	{
		len = skip_quotes(tmp + start);
		while (ft_strchr(set, tmp[start + len]) == 0 && \
				(tmp[start + len] != '\'' || tmp[start + len] != '"'))
			len++;
		if (len)
			split[j++] = ft_substr(tmp, start, len);
		while (ft_strchr(set, tmp[start + len]) != 0 && tmp[start + len])
			len++;
		start += len;
	}
	if (tmp)
		free(tmp);
	return (split);
}

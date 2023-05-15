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
		while (ft_strchr(set, tmp[i]) != 0)
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
	return (NULL);
}

//splits string based if character in set is found
char	**ft_split_set(char *str, char *set)
{
	int		i;
	int		j;
	char	*tmp;
	char	**split;

	tmp = ft_strtrim(str, set);
	j = 0;
	split = ft_calloc(sizeof(char *), cnt_cmd(str, set) + 1);
	if (!split)
		empty_set(split);
	while (*tmp)
	{
		i = skip_quotes(tmp);
		while (ft_strchr(set, tmp[i]) == 0 && \
				(tmp[i] != '\'' || tmp[i] != '"'))
			i++;
		if (i)
			split[j++] = ft_substr(tmp, 0, i);
		while (ft_strchr(set, tmp[i]) != 0)
			i++;
		tmp += i;
	}
	free(tmp);
	return (split);
}

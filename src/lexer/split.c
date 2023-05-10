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
		else
		{
			while (ft_strchr(set, tmp[i]) != 0)
				i++;
		}
		tmp += i;
	}
	return (j);
}
/*
static int	cnt_cmd(char *str, char *set)
{
	int		i;
	int		cnt;
	char	*trim;

	i = 0;
	cnt = 0;
	trim = ft_strtrim(str, set);
	if (ft_strchr(set, trim[i]) == NULL)
		cnt++;
	while (trim[i])
	{
		if (ft_strchr(set, trim[i]) != NULL)
			cnt++;
		i++;
	}
	free(trim);
	return (cnt);
}
*/

//checks size of command based on character set
/*
static size_t	get_cmd_size(char *str, char *set)
{
	size_t	size;

	size = 0;
	while (*str && ft_strchr(set, *str) == 0)
	{
		size++;
		str++;
	}
	return (size);
}
*/

//empty 2D array after use/in case of error
static void	*empty_set(char **str)
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
		else
		{
			while (ft_strchr(set, tmp[i]) != 0)
				i++;
		}
		tmp += i;
	}
	return (split);
}

/*
char	**ft_split_set(char *str, char *set)
{
	char	**cmd;
	int		i;
	int		j;
	int		len;

	if (!str || !set)
		return (NULL);
	len = cnt_cmd(str, set);
	cmd = ft_calloc(len + 1, sizeof(char *));
	if (!cmd)
		return (NULL, empty_set(cmd));
	i = 0;
	while (i < len && *str)
	{
		while (*str && ft_strchr(set, *str) != 0)
			str++;
		cmd[i] = ft_calloc(get_cmd_size(str, set) + 1, sizeof(char));
		if (cmd[i] == NULL)
			return (empty_set(cmd));
		j = 0;
		while (*str && ft_strchr(set, *str) == 0)
			cmd[i][j++] = *str++;
		i++;
	}
	return (cmd);
}
*/
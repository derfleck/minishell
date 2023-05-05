#include "../inc/minishell.h"

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

size_t	get_cmd_size(char *str, char *set)
{
	size_t	size;

	size = 0;
	while (*str && ft_strchr(set, *str) == NULL)
	{
		size++;
		str++;
	}
	return (size);
}

char	**ft_split_set(char *str, char *set)
{
	char	**cmd;
	int		i;
	int		j;

	if (!str || !set)
		return (NULL);
	cmd = ft_calloc(cnt_cmd(str, set) + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (cmd[i] && *str)
	{
		while (*str && ft_strchr(set, *str) != NULL)
			str++;
		cmd[i] = ft_calloc(get_cmd_size(str, set), sizeof(char));
		if (cmd[i] == NULL)
			return (NULL);
		//TODO: add free if something fails
		j = 0;
		while (*str && ft_strchr(set, *set) != NULL)
			cmd[i][j++] = *str++;
		i++;
	}
	return (cmd);
}

//only syntax check after this line

//skips quotes in string, returns value how many characters to skip
int	skip_quotes(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
	{
		while (str[++i] && str[i] != '\'')
			;
	}
	if (str[i] == '"')
	{
		while (str[++i] && str[i] != '"')
			;
	}
	return (i);
}

//counts how many times c occurs in str, ignores quoted text
int	count_char(char *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		i += skip_quotes(str[i]);
		if (str[i] == c)
			cnt++;
		if (str[i])
			i++;
	}
	return (cnt);
}

//checks if line entered has a correct syntax
//first check: counts if # of brackets matches up
int	syntax_check(char *str)
{
	int i;

	i = 0;
	if (count_char(str, '(') != count_char(str, ')'))
		return (0);
	while (str[i])
	{
		i += skip_quotes(str[i]);
		if (str[i] == ';' || str[i] == '\\')
			return (0);
		if (str[i])
			i++;
	}
	return (1);
}

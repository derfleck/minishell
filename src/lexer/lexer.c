#include "../../inc/minishell.h"

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
//not really necessary for parantheses, as subject specifies
//no special characters should be handled which aren't mentioned
int	count_char(char *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (c != '\'' && c != '"')
			i += skip_quotes(str + i);
		if (str[i] == c)
			cnt++;
		if (str[i])
			i++;
	}
	return (cnt);
}

//checks if line entered has a correct syntax (closed quotes)
int	syntax_check(char *str)
{
	int		i;
	char	tmp;

	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] != '\'' && str[i] != '"'))
		{
			if (str[i] == ';' || str[i] == '\\')
				return (0);
			i++;
		}
		if (!str[i])
			break ;
		else
		{
			tmp = str[i];
			i += skip_quotes(str + i);
		}
		if (!str[i] && str[i - 1] != tmp)
			return (0);
	}
	return (1);
}

//checks if character is a separating token (|/</>)
t_type	check_token(char c)
{
	static int	token[3][2] = {{'|', PIPE}, \
								{'>', GREAT}, \
								{'<', LESS}};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (c == token[i][0])
			return (token[i][1]);
		i++;
	}
	return (0);
}

//classifies a one or two character string as token
t_type	classify_token(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i++ > 1 || (str[i] != '>' || str[i] != '<' || str[i] != '|'))
			return (0);
	}
	if (str[1])
	{
		if (check_token(str[0]) == GREAT && \
		check_token(str[1]) == GREAT)
			return (GREAT_GREAT);
		else if (check_token(str[0]) == LESS && \
			check_token(str[1]) == LESS)
			return (LESS_LESS);
		else
			return (0);
	}
	else
		return (check_token(str[0]));
	return (0);
}

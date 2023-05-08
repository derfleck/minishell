#include "../inc/minishell.h"

typedef enum s_type {
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_type;

typedef struct s_lexer {
	char			*str;
	t_type			token;
	int				i;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

/*
int	main(void)
{
	char	**str;
	int	i = 0;

	str = ft_split_set("ls -l | wc -l >> test", " ");
	while (str[i])
		printf("%s\n", str[i++]);
	return (i);
}
*/

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
		i += skip_quotes(str[i]);
		if (str[i] == c)
			cnt++;
		if (str[i])
			i++;
	}
	return (cnt);
}

//checks if line entered has a correct syntax
//if an odd number of quotes is encountered, heredoc should be launched
//with quote/dquote as prompt until missing character is used (maybe?)
int	syntax_check(char *str)
{
	int	i;

	i = 0;
	if ((count_char(str, '\'') % 2 == 1) || (count_char(str, '"') % 2 == 1))
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
		if (i++ > 1)
			return (0);
	}
	i = 0;
	while (str[i])
	{
		if (str[i + 1])
		{
			if (check_token(str[i]) == GREAT && \
			check_token(str[i + 1] == GREAT))
				return (GREAT_GREAT);
			else if (check_token(str[i]) == LESS && \
			check_token(str[i + 1] == LESS))
				return (LESS_LESS);
		}
		else
			return (check_token(str[i]));
		i++;
	}
	return (0);
}

//creates new linked list for lexer, needs token count
t_lexer	*new_lexer_list(char **cmd, int i)
{
	int		j;
	t_lexer	*lex;

	j = 0;
	lex = ft_calloc(sizeof(t_lexer), i);
	if (!lex)
		return (NULL);
	while (cmd[j])
	{
		lex[j].i = j;
		lex[j].str = cmd[i];
		lex[j].token = classify_token(cmd[i]);
		if (j < i - 1)
			lex[j].next = lex[j + 1];
		else
			lex[j].next = lex[0];
		if (j == 0)
			lex[j].prev = lex[i - 1];
		else
			lex[j].prev = lex[j - 1];
		j++;
	}
	return (lex);
}

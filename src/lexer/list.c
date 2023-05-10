#include "../../inc/minishell.h"

//creates new linked list for lexer, needs token count
static t_lexer	*new_lexer_list(char **cmd, int i)
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
		lex[j].str = cmd[j];
		lex[j].token = classify_token(cmd[j]);
		if (j < i - 1)
			lex[j].next = (lex + j + 1);
		else
			lex[j].next = lex;
		if (j == 0)
			lex[j].prev = (lex + i - 1);
		else
			lex[j].prev = (lex + j - 1);
		j++;
	}
	return (lex);
}

//starts the lexer
t_lexer	*start_lexer(char *str)
{
	int			i;
	char		**split;
	t_lexer		*lex;
	static char	set[6] = " \t\n\v\f\r";

	i = 0;
	split = ft_split_set(str, set);
	//if (!syntax_check(str) && split)
	//	return (free(str), NULL);
	if (!split)
		return (NULL);
	while (split[i])
		i++;
	lex = new_lexer_list(split, i);
	if (!lex)
		return (NULL);
	free(split);
	return (lex);
}

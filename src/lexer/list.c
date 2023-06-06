#include "../../inc/minishell.h"

//creates new linked list for lexer, needs token count
static t_lexer	*new_lexer_list(char **cmd, int i)
{
	int		j;
	t_lexer	*lex;

	j = 0;
	lex = ft_calloc(i, sizeof(t_lexer));
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
			lex[j].next = NULL;
		if (j == 0)
			lex[j].prev = NULL;
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
	if (!syntax_check(str))
		return(perror("Syntax error"), free(str), NULL);
	split = ft_split_set(str, set);
	if (!split)
		return (NULL);
	while (split[i])
		i++;
	lex = new_lexer_list(split, i);
	if (!lex)
		return (NULL);
	//empty_set(split);
	return (lex);
}

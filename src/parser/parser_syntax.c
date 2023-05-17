#include "../../inc/minishell.h"

//checks if single tokens at beginning or end or in succession
//returns number of command groups separated by pipes
//needs to be adapted for error messages (or replaced by something else)
static int	parse_check(t_lexer *lex)
{
	int		cmd;
	t_lexer	*tmp;

	tmp = lex;
	cmd = 0;
	while (tmp && tmp->token != PIPE)
	{
		if ((tmp->token == PIPE && (tmp->prev == NULL || tmp->next == NULL)) \
		|| (tmp->next == NULL && tmp->token))
		{
			if (tmp->token == PIPE && tmp->prev == NULL)
				printf("syntax error near unexpected token %s", tmp->str);
			else if (tmp->next == NULL && tmp->token)
				printf("syntax error near unexpected token `newline'");
			return (0);
		}
		while (tmp)
		{
			if (tmp->token == PIPE)
				break ;
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
		cmd++;
	}
	return (cmd);
}

//executes parse check and creates new parse list
//returns NULL on syntax or malloc error
t_cmd	**create_parse_list(t_lexer *lex)
{
	t_cmd	**tmp;
	int		n_cmd;
	int		i;
	int		j;

	j = 0;
	i = 0;
	n_cmd = parse_check(lex);
	if (!n_cmd)
		return (NULL);
	tmp = malloc(sizeof(t_cmd *) * n_cmd);
	if (!tmp)
		return (NULL);
	while (j < n_cmd)
		tmp[j++] = create_parse_node(lex + i, &i, n_cmd);
	return (tmp);
}

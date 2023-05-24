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
	while (tmp)
	{
		if ((tmp->token == PIPE && (tmp->prev == NULL || tmp->next == NULL)) \
		|| (tmp->next == NULL && tmp->token))
		{
			if (tmp->token == PIPE && tmp->prev == NULL)
				printf("minishell: syntax error near unexpected token %s", tmp->str);
			else if (tmp->next == NULL && tmp->token)
				printf("minishell: syntax error near unexpected token `newline'");
			return (0);
		}
		while (tmp && tmp->token != PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
		cmd++;
	}
	return (cmd);
}

//creates node with number of special tokens
static t_lexer	*create_parse_node(t_lexer *lex, int n_cmd, t_cmd *cmd)
{
	t_lexer	*tmp;

	tmp = lex;
	cmd->num[CMD] = n_cmd;
	count_arg_redir(lex, cmd);
	create_words(cmd, lex);
	while (tmp && tmp->token != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->token == PIPE)
		tmp = tmp->next;
	if (!tmp)
		cmd->next = NULL;
	else
		cmd->next = cmd + 1;
	return (tmp);
}

//executes parse check and creates new parse list
//returns NULL on syntax or malloc error
//parse_check returns the number of command groups
t_cmd	*create_parse_list(t_lexer *lex)
{
	t_cmd	*cmd;
	t_lexer	*tmp;
	int		n_cmd;
	int		j;

	j = -1;
	tmp = lex;
	n_cmd = parse_check(lex);
	if (!n_cmd)
		return (NULL);
	cmd = ft_calloc(n_cmd, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (++j < n_cmd)
		tmp = create_parse_node(tmp, n_cmd, cmd + j);
	return (cmd);
}

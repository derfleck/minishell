#include "../../inc/minishell.h"

//iterates through 2D array till first occurence of NULL
static int	move_to_empty(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

//allocates memory for the pieces of the t_cmd struct
//TODO: add error for malloc fail
static void	init_cmd_struct(t_cmd *cmd)
{
	cmd->arg = ft_calloc(cmd->num[ARG] + 1, sizeof(char *));
	if (!cmd->arg)
		return ;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->here = ft_calloc(cmd->num[HERE] + 1, sizeof(char *));
	if (!cmd->here)
		return ;
}

//assigns cmd/arg/here stopwords to string arrays in cmd struct
//checks for last in/out tokens and stores pointer to lexer node
static void	assign_word(t_cmd *cmd, t_lexer *lex)
{
	if (!(lex->token) && cmd->cmd == NULL)
		cmd->cmd = lex->str;
	else if (!(lex->token) && cmd->cmd != NULL)
		cmd->arg[move_to_empty(cmd->arg)] = lex->str;
	else if (lex->token == GREAT || lex->token == GREAT_GREAT)
		cmd->out = lex;
	else if (lex->token == LESS || lex->token == LESS_LESS)
	{
		cmd->in = lex;
		if (lex->token == LESS_LESS && lex->next)
			cmd->here[move_to_empty(cmd->here)] = lex->next->str;
	}
}

//counts types of special tokens in lexer list
//iterates throug list until first occurence of pipe
//returns pointer to position in lexer list
void	count_arg_redir(t_lexer *lex, t_cmd *cmd)
{
	t_lexer	*tmp;

	tmp = lex;
	if (tmp->token == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == 0)
			cmd->num[ARG]++;
		else
		{
			if (tmp->token == LESS_LESS)
				cmd->num[HERE]++;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

//iterates through lexer list and allocates words
//to command structure as needed
void	create_words(t_cmd *cmd, t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	init_cmd_struct(cmd);
	if (tmp->token == PIPE)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->token)
		{
			if (tmp->token == PIPE)
				break ;
			else
				assign_word(cmd, tmp);
			tmp = tmp->next;
		}
		else
			assign_word(cmd, tmp);
		if (tmp)
			tmp = tmp->next;
	}
}

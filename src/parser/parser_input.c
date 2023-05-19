#include "../../inc/minishell.h"

//counts types of special tokens in lexer list
//iterates throug listuntil first occurence of pipe
//returns pointer to position in lexer list
t_lexer	*count_arg_redir(t_lexer *lex, t_cmd *cmd)
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
			if (tmp->token == GREAT)
				cmd->num[OUT]++;
			else if (tmp->token == GREAT_GREAT)
				cmd->num[APP]++;
			else if (tmp->token == LESS)
				cmd->num[IN]++;
			else if (tmp->token == LESS_LESS)
				cmd->num[HERE]++;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

//writes tokens with filenames and stop words to
//the in and out structs, still uses the strings
//from lexer list
void	handle_in_out(t_cmd *cmd, t_lexer *lex)
{
	t_in	*in;
	t_out	*out;

	in = cmd->in;
	out = cmd->out;
	if (lex->token == GREAT || lex->token == GREAT_GREAT)
	{
		out->last = lex;
		if (lex->token == GREAT)
			out->output[move_to_empty(out->output)] = lex->next->str;
		else if (lex->token == GREAT_GREAT)
			out->append[move_to_empty(out->append)] = lex->next->str;
	}
	else
	{
		in->last = lex;
		if (lex->token == LESS)
			in->input[move_to_empty(in->input)] = lex->next->str;
		else if (lex->token == LESS_LESS)
			in->here[move_to_empty(in->here)] = lex->next->str;
	}
}

//assigns words to string arrays in cmd struct
void	assign_word(t_cmd *cmd, t_lexer *lex)
{
	if (!(lex->token) && cmd->cmd == NULL)
		cmd->cmd = lex->str;
	else if (!(lex->token) && cmd->cmd != NULL)
		cmd->arg[move_to_empty(cmd->arg)] = lex->str;
	else
		handle_in_out(cmd, lex);
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
		tmp = tmp->next;
	}
}

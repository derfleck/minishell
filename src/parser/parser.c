#include "../../inc/minishell.h"

//counts types of special tokens in lexer list
//returns 0 if token isn't followed by a word, 1 on success
static int	count_arg_redir(t_lexer *lex, int *i, t_cmd *cmd)
{
	while ((lex + *i) && lex[*i].token != PIPE)
	{
		if (!lex[*i].token)
			cmd->num[ARG]++;
		else
		{
			if (lex[*i].token == GREAT)
				cmd->num[OUT]++;
			else if (lex[*i].token == GREAT_GREAT)
				cmd->num[APP]++;
			else if (lex[*i].token == LESS)
				cmd->num[IN]++;
			else if (lex[*i].token == LESS_LESS)
				cmd->num[HERE]++;
			(*i)++;
			if (lex[*i].token == 0)
				(*i)++;
			else
				return (0);
		}
		(*i)++;
	}
	return (1);
}

//iterates through 2D array till first occurence of NULL
static int	move_to_empty(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

//assigns words to string arrays in cmd struct
static void	assign_word(t_cmd *cmd, t_lexer *lex)
{
	if (!(lex->token) && cmd->cmd == NULL)
		cmd->cmd = ft_strdup(lex->str);
	else if (!(lex->token) && cmd->cmd != NULL)
		cmd->arg[move_to_empty(cmd->arg)] = ft_strdup(lex->str);
	else
	{
		if (lex->token == GREAT)
			cmd->output[move_to_empty(cmd->output)] = ft_strdup(lex->next->str);
		else if (lex->token == GREAT_GREAT)
			cmd->append[move_to_empty(cmd->append)] = ft_strdup(lex->next->str);
		else if (lex->token == LESS)
			cmd->input[move_to_empty(cmd->input)] = ft_strdup(lex->next->str);
		else if (lex->token == LESS_LESS)
			cmd->here[move_to_empty(cmd->here)] = ft_strdup(lex->next->str);
	}
}

//mallocs amount of words for redirects
//then assigns them individually
static void	create_words(t_cmd *cmd, t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	cmd->cmd = NULL;
	cmd->arg = ft_calloc(cmd->num[ARG] + 1, sizeof(char *));
	cmd->input = ft_calloc(cmd->num[IN] + 1, sizeof(char *));
	cmd->output = ft_calloc(cmd->num[OUT] + 1, sizeof(char *));
	cmd->append = ft_calloc(cmd->num[APP] + 1, sizeof(char *));
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

//creates node with number of special tokens
//TODO: add error messages for syntax check in count_arg_redir
t_cmd	*create_parse_node(t_lexer *lex, int *i, int n_cmd)
{
	t_cmd	*cmd;
	int		num;

	num = 1;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_strdup(lex[*i].str);
	cmd->num[CMD] = n_cmd;
	while (num <= HERE)
		cmd->num[num++] = 0;
	if (!count_arg_redir(lex, i, cmd))
		return (NULL);
	create_words(cmd, lex);
	return (cmd);
}

/*
//initializes new cmd struct for linked list
t_cmd	*init_cmd_node(char *str, t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (prev)
		prev->next = cmd;
	cmd->cmd = str;
	cmd->arg = NULL;
	cmd->num_arg = 0;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->append = NULL;
	cmd->next = NULL;
	return (cmd);
}

//counts number of items in lexer list until next pipe
//returns int with number of items in cmd group
int	count_group(t_lexer	*lex)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	tmp = lex;
	while (tmp->token != PIPE || tmp->next->i == 0)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}


t_cmd	*split_cmd(t_lexer *lex)
{
	int		i;
	int		j;
	int		k;
	t_cmd	*cmd;
	t_lexer	*tmp;

	i = 0;
	tmp = lex;
	cmd = ft_calloc(sizeof(t_cmd), parse_check(lex));
	if (!cmd)
		return (NULL);
	while (cmd + i)
	{
		if (!tmp->token)
		{
			cmd[i].cmd = ft_strdup(tmp->str);
			tmp = tmp->next;
		}
		j = count_group(tmp);
		k = 0;
		cmd[i].arg = ft_calloc(sizeof(char *), j + 1);
		while (k < j)
			cmd[i].arg[k++] = ft_strdup(tmp->str);
	}
}
*/

//expander: remove quotations, search for env variable if "" and closed
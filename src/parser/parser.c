#include "../../inc/minishell.h"

//define a rule that combines all words starting with a quote 

//arguments for execve needs to be provided as 2D array

//echo treats arguments different, everything except -n flag is a continuous string, just join them with a single space in between

//simple rule: check for words until token, invalid if token at error of lexer list or if two tokens follow each other with no words in between

//search for redirection tokens and then put them into another lexer list, take them out of the original lexer list


//if two single tokens (pipe, great, less) are in succession, print error message: syntax error near unexpected token ''

//there can be only one heredoc as it is usually redirected to stdout

//heredoc mode can only stop if the line actually ends with the stopword, no trailing characters (not even whitespace)
//when there's multiple heredocs, the first stopword needs to be entered and only then the second heredoc starts

//just iterate through the 2D-array, assign pointers to the command, iterate through all the arguments and store the number of arguments (don't need to reassign)


typedef struct	s_cmd {
	char			*cmd;
	char			**arg;
	int				num_arg;
	char			**input;
	char			**output;
	char			**append;
	struct s_cmd	*next;
}				t_cmd;

//checks if single tokens at beginning or end or in succession
//returns number of command groups separated by pipes
//needs to be adapted for error messages (or replaced by something else)
int	parse_check(t_lexer *lex)
{
	int		i;
	int		cmd;
	t_lexer	*tmp;

	tmp = lex;
	i = tmp->i;
	cmd = 0;
	while (tmp->i == i)
	{
		if ((tmp->token == PIPE && i == 0) || (tmp->next->i == 0 && tmp->token))
		{
			if (tmp->token == PIPE && tmp->i == 0)
				printf("syntax error near unexpected token %s", tmp->str);
			else if (tmp->next->i == 0 && tmp->token)
				printf("syntax error near unexpected token `newline'");
			return (0);
		}
		while (tmp->token != PIPE)
		{
			tmp = tmp->next;
			i++;
		}
		cmd++;
	}
	return (cmd);
}

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

void	parse_arguments(t_cmd *cmd, t_lexer	*lex, int *i)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp->i == *i)
	{

	}
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

t_lexer	*parse_group(t_lexer *lex, t_cmd *cmd, int *i)
{
	int	j;

	j = count_group(lex);
	while (j--)
	{
		
	}
	i++;
	return (lex);
}

t_cmd	*create_cmd_list(t_lexer *lex)
{
	t_cmd	*cmd;
	t_lexer	*tmp;
	int		i;
	int		cmds;

	i = 0;
	tmp = lex;
	cmds = parse_check(lex);
	if (!cmds)
		return (NULL);
	while (i < cmds)
		tmp = parse_group(tmp, cmd + i, &i);
}



/*
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
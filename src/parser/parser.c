#include "../../inc/minishell.h"

//define a rule that combines all words starting with a quote 

//arguments for execve needs to be provided as 2D array

//echo treats arguments different, everything except -n flag is a continuous string, just join them with a single space in between

//simple rule: check for words until token, invalid if token at error of lexer list or if two tokens follow each other with no words in between

//search for redirection tokens and then put them into another lexer list, take them out of the original lexer list


//if two single tokens (pipe, great, less) are in succession, print error message: syntax error near unexpected token ''

//there can be only one heredoc as it is usually redirected to stdout

typedef struct	s_cmd {
	char			*cmd;
	char			**arg;
	t_parse			type;
	int				here_doc;
	int				num_red;
	struct s_cmd	*next;
}				t_cmd;

typedef	struct	s_redir {
	char		*in;
	char		*out;
	int			in_fd;
	int			out_fd;
}				t_redir;

//checks if single tokens at beginning or end or in succession
//returns number of command groups separated by pipes
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
		if ((tmp->token == PIPE && tmp->i == 0) || \
		(tmp->next->i == 0 && tmp->token))
		{
			if (tmp->token == PIPE && tmp->i == 0)
				printf("minishell: syntax error \
				near unexpected token %s", tmp->str);
			else if (tmp->next->i == 0 && tmp->token)
				printf("syntax error near unexpected token `newline'");
			return (0);
		}
		while (tmp->token != PIPE)
			tmp = tmp->next;
		cmd++;
	}
	return (cmd);
}

int		count_group(t_lexer	*lex)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	tmp = lex;
	while (tmp->token != PIPE)
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

//expander: remove quotations, search for env variable if "" and closed
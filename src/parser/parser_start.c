#include "../../inc/minishell.h"

//checks if tokens have a corresponding word or if pipe is at correct pos
static int	token_check(t_lexer *tmp)
{
	if (tmp && \
		((tmp->token == PIPE && \
		(tmp->prev == NULL || tmp->next == NULL || tmp->prev->token)) \
		|| (tmp->next == NULL && tmp->token) || \
		(tmp->token && tmp->token != PIPE && tmp->prev && tmp->prev->token)))
	{
		if (tmp->token && tmp->next == NULL)
			ft_putendl_fd(TOKEN_WARN_NEW, STDERR_FILENO);
		else
		{
			ft_putstr_fd(TOKEN_WARN_CHR, STDERR_FILENO);
			ft_putendl_fd(tmp->str, STDERR_FILENO);
		}
		g_stat = 2;
		return (0);
	}
	return (1);
}

//checks if single tokens at beginning or end or in succession
//returns number of command groups separated by pipes
//needs to be adapted for error messages (or replaced by something else)
static int	parse_check(t_lexer *lex)
{
	int		cmd;
	t_lexer	*tmp;

	tmp = lex;
	cmd = 1;
	while (tmp)
	{
		while (tmp && !tmp->token)
			tmp = tmp->next;
		if (!token_check(tmp))
			return (0);
		if (tmp && tmp->token == PIPE)
			cmd++;
		if (tmp)
			tmp = tmp->next;
	}
	return (cmd);
}

//creates node with number of special tokens
static t_lexer	*create_parse_node(t_lexer *lex, int n_cmd, t_cmd *cmd, int j)
{
	t_lexer	*tmp;

	tmp = lex;
	cmd->start = lex;
	cmd->num[CMD] = n_cmd;
	cmd->i = j;
	count_arg_redir(lex, cmd);
	if (create_words(cmd, lex))
		return (NULL);
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

//added late to have a pointer to the env head in every
//cmd node
static void	add_env_to_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		tmp->head = env;
		tmp = tmp->next;
	}
}

//executes parse check and creates new parse list
//returns NULL on syntax or malloc error
//parse_check returns the number of command groups
t_cmd	*create_parse_list(t_lexer *lex, t_env *env)
{
	t_cmd	*cmd;
	t_lexer	*tmp;
	int		n_cmd;
	int		j;

	j = -1;
	tmp = lex;
	n_cmd = parse_check(lex);
	if (!n_cmd)
		return ((t_cmd *)free_lex(lex));
	cmd = ft_calloc(n_cmd, sizeof(t_cmd));
	if (!cmd)
		return ((t_cmd *)free_lex(lex));
	while (++j < n_cmd && tmp)
		tmp = create_parse_node(tmp, n_cmd, cmd + j, j);
	if (j != n_cmd && tmp == NULL)
		free_cmd(cmd);
	add_env_to_cmd(cmd, env);
	return (cmd);
}

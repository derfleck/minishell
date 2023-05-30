#include "../../inc/minishell.h"

//checks if token is a redirection token
static int is_redir(t_lexer *lex)
{
	if (lex->token == GREAT || lex->token == GREAT_GREAT || \
		lex->token == LESS || lex->token == LESS_LESS)
		return (1);
	else
		return (0);
}

//tries to open the file and returns file descriptor
static int	try_open(t_lexer *lex)
{
	int fd;

	fd = 0;
	if (lex->token == LESS && lex->next)
		fd = open(lex->next->str, O_RDONLY);
	else if (lex->token == GREAT && lex->next)
		fd = open(lex->next->str, O_CREAT | O_WRONLY | O_TRUNC);
	else if (lex->token == GREAT_GREAT && lex->next)
		fd = open(lex->next->str, O_CREAT | O_APPEND);
	if (fd)
		close(fd);
	return (fd);
}

//opens all provided files, both input and output
//throws an error on first input file that can't be opened (in order)
//creates files which don't exist yet for output
//returns 1 on success, 0 on error, stops at error in list
int	open_files(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = lex;
	while (tmp && tmp->token != PIPE)
	{
		while (tmp && !is_redir(tmp))
			tmp = tmp->next;
		if (tmp && tmp->next && try_open(tmp) == -1)
		{
			write(STDOUT_FILENO, "minishell: ", 11);
			perror(tmp->next->str);
			return (0);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

//opens last in and out files and assigns fd to cmd struct
void	open_in_out(t_cmd *cmd)
{
	if (cmd->in != NULL)
	{
		if (cmd->in->token == LESS)
			cmd->fd[IN] = open(cmd->in->next->str, O_RDONLY);
		else if (cmd->in->token == LESS_LESS)
			cmd->fd[IN] = start_heredoc(cmd);
		else
			cmd->fd[IN] = STDIN_FILENO;
	}
	if (cmd->out != NULL)
	{
		if (cmd->out->token == GREAT)
			cmd->fd[OUT] = open(cmd->out->next->str, O_CREAT | O_WRONLY | O_TRUNC);
		else if (cmd->in->token == GREAT_GREAT)
			cmd->fd[OUT] = open(cmd->out->next->str, O_CREAT | O_APPEND);
		else
			cmd->fd[OUT] = STDOUT_FILENO;
	}
}

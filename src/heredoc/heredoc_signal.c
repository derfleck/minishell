#include "../../inc/minishell.h"

static char *expand_heredoc(char *input, t_cmd *cmd)
{
	char *tmp;

	tmp = NULL;
	if (input)
	{
		tmp = expander(input, cmd->head);
		input = free_ptr(input);
	}
	return (tmp);
}

//helper function to empty file after SIGINT
static void	empty_file(t_cmd *cmd)
{
	int	fd;

	if (cmd->here_file != NULL)
	{
		fd = open(cmd->here_file, O_WRONLY | O_TRUNC);
		if (fd != -1)
			close(fd);
	}
}

int	*check_sigint(void)
{
	static int	*pressed;

	if (!pressed)
	{
		pressed = (int *)malloc(sizeof(int));
		*pressed = 0;
	}
	return (pressed);
}

void	sig_handler_heredoc(int sig_num)
{
	int		*pressed;
	char	newline;

	newline = '\n';
	pressed = check_sigint();
	if (sig_num == SIGINT)
	{
		*pressed = 1;
		write(STDOUT_FILENO, "^C", 3);
		ioctl(STDIN_FILENO, TIOCSTI, &newline, sizeof(newline));
		signal(SIGINT, sig_handler_heredoc);
	}
	else if (sig_num == SIGQUIT)
	{
		ft_putstr_fd("minishell: warning : here-document deli", STDOUT_FILENO);
		ft_putstr_fd("mited by end-of-file (wanted `here`)\n", STDOUT_FILENO);
	}
}

void	heredoc_loop(t_cmd	*cmd, int i, int fd, char *input)
{
	while (*(check_sigint()) != 1)
	{
		input = readline("> ");
		if (*(check_sigint()) == 1)
			empty_file(cmd);
		if (*(check_sigint()) != 1 && i == cmd->num[HERE] - 1)
		{
			if (!input || ft_strcmp(input, cmd->here[i]))
			{
				input = free_ptr(input);
				break ;
			}
			input = expand_heredoc(input, cmd);
			if (write(fd, input, ft_strlen(input)) == -1 || \
				write(fd, "\n", 1) == -1)
			{
				input = free_ptr(input);
				break ;
			}
		}
		else if (*(check_sigint()) != 1 && input \
					&& ft_strcmp(input, cmd->here[i]))
			i++;
		input = free_ptr(input);
	}
}

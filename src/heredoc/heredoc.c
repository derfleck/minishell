#include "../../inc/minishell.h"

static void	child_heredoc(t_shell *sh, t_cmd *cmd)
{
	int		fd;
	int		i;
	char	*input;

	i = 0;
	input = NULL;
	fd = open(cmd->here_file, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return ;
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler_heredoc);
	signal(SIGQUIT, SIG_DFL);
	heredoc_loop(cmd, i, fd, input);
	close(fd);
	cmd->here_file = free_ptr(cmd->here_file);
	if (sh->head != NULL)
		sh->head = free_env_list(&sh->head);
	if (sh != NULL)
		sh = free_shell(sh);
	if (*(check_sigint()) == 1)
		g_stat = 130;
	free_ptr(check_sigint());
	exit (g_stat);
}

//starts the heredoc mode, iterates through all stopwords
//IMPORTANT: should always be started if heredoc stopwords provided
static int	start_heredoc(t_shell *sh, t_cmd *cmd)
{
	char	*number;
	pid_t	pid;
	int		p_status;

	p_status = 0;
	number = ft_itoa(cmd->i);
	cmd->here_file = ft_strjoin("here_", number);
	free(number);
	set_sigaction(-1);
	pid = fork();
	if (pid == CHILD)
		child_heredoc(sh, cmd);
	else
		waitpid(pid, &p_status, 0);
	if (WIFEXITED(p_status))
		g_stat = WEXITSTATUS(p_status);
	set_sigaction(PARENT);
	return (g_stat);
}

//signal handler for SIGINT in heredoc mode
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
}

//runs heredoc in the beginning for all command groups
int	run_heredoc(t_shell *sh, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->num[HERE] > 0)
		{
			if (start_heredoc(sh, tmp) > 0)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

//closes and unlinks temporary heredoc
//therefore removing it from the disk
int	unlink_heredoc(t_cmd *cmd)
{
	if (cmd && cmd->num[HERE] > 0)
	{
		if (cmd->fd[IN])
			close(cmd->fd[IN]);
		if (cmd->here_file && unlink(cmd->here_file) == -1)
			;
		if (cmd->here_file)
			cmd->here_file = free_ptr(cmd->here_file);
	}
	return (1);
}

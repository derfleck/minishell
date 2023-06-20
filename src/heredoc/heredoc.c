#include "../../inc/minishell.h"

static void	heredoc_loop(t_cmd	*cmd, int i, int fd, char *input)
{
	while (1)
	{
		input = readline("> ");
		if (i == cmd->num[HERE] - 1)
		{
			if (!input || ft_strcmp(input, cmd->here[i]))
			{
				free(input);
				break ;
			}
			if ((write(fd, input, ft_strlen(input)) == -1 || \
				write(fd, "\n", 1) == -1))
			{
				free(input);
				break ;
			}
		}
		else
		{
			if (input && ft_strcmp(input, cmd->here[i]))
				i++;
		}
		free(input);
	}
}
/*
static void	check_heredoc(t_cmd *cmd, int fd)
{
	char	buf[1];
	ssize_t	ret;
	off_t	size;

	size = 0;
	while ((ret = read(fd, buf, sizeof(buf))) > 0)
		size += ret;
	if (size == 0) {
		ft_putstr_fd("minishell: warning : here-document deli", STDOUT_FILENO);
		ft_putstr_fd("mited by end-of-file (wanted `here`)\n", STDOUT_FILENO);
		unlink_heredoc(cmd);
		cmd->here_file = NULL;
	}

}
*/

//starts the heredoc mode, iterates through all stopwords
//IMPORTANT: should always be started if heredoc stopwords provided
static char	*start_heredoc(t_cmd *cmd)
{
	int		fd;
	int		i;
	char	*input;
	char	*number;

	number = ft_itoa(cmd->i);
	cmd->here_file = ft_strjoin("here_", number);
	free(number);
	i = 0;
	input = NULL;
	fd = open(cmd->here_file, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (NULL);

	
	heredoc_loop(cmd, i, fd, input);
	//check_heredoc(cmd, fd);
	
	
	close(fd);
	return (cmd->here_file);
}

//runs heredoc in the beginning for all command groups
void	run_heredoc(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->num[HERE] > 0)
			start_heredoc(tmp);
		tmp = tmp->next;
	}
}

//closes and unlinks temporary heredoc
//therefore removing it from the disk
int		unlink_heredoc(t_cmd *cmd)
{
	if (cmd->num[HERE] > 0)
	{
		if (cmd->fd[IN])
			close(cmd->fd[IN]);
		if (cmd->here_file && unlink(cmd->here_file) == -1)
		{
			perror("Error while unlinking");
			return (0);
		}
		if (cmd->here_file)
			free(cmd->here_file);
	}
	return (1);
}
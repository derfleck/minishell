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

//starts the heredoc mode, iterates through all stopwords
//IMPORTANT: should always be started if heredoc stopwords provided
char	*start_heredoc (t_cmd *cmd)
{
	int     fd;
	int		i;
	char	*input;
	char	*tmp;
	char	*out;

	i = 0;
	input = NULL;
	fd = open("here_tmp", O_CREAT | O_EXCL | O_WRONLY, 0600);
	out = "";
	if (fd == -1)
		return (NULL);
	heredoc_loop(cmd, i, fd, input);
	tmp = get_next_line(fd);
	while (tmp)
	{
		out = ft_strjoin(out, tmp);
		tmp = get_next_line(fd);
	}
	if (close(fd) == -1 || unlink("here_tmp") == -1)
		return (NULL);
	return (out);
}

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
int	start_heredoc (t_cmd *cmd)
{
	int     fd;
	int		i;
	char	*input;
	char	*filename;

	filename = ft_strjoin("here_", (char)cmd->i + 48);
	i = 0;
	input = NULL;
	fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0600);
	free(filename);
	if (fd == -1)
		return (NULL);
	heredoc_loop(cmd, i, fd, input);
	return (fd);
}

/*
//reads heredoc, closes and writes it to a string and returns it
char	*read_heredoc(int fd, char *filename)
{
	char	*tmp;
	char	*out;

	out = "";
	tmp = get_next_line(fd);
	while (tmp)
	{
		out = ft_strjoin(out, tmp);
		tmp = get_next_line(fd);
	}
	if (close(fd) == -1 || unlink(filename) == -1)
		return (NULL);
	return (tmp);
}
*/
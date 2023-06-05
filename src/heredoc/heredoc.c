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
char	*start_heredoc(t_cmd *cmd)
{
	int		fd;
	int		i;
	char	*input;
	char	*filename;
	char	*number;

	number = ft_itoa(cmd->i);
	filename = ft_strjoin("here_", number);
	i = 0;
	input = NULL;
	fd = open(filename, O_CREAT | O_RDWR, 0644);
	//free(filename);
	free(number);
	if (fd == -1)
		return (NULL);
	heredoc_loop(cmd, i, fd, input);
	close(fd);
	return (filename);
}

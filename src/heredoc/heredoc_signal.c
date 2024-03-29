/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:33:10 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/29 12:33:14 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//performs expansion on heredoc input
//executed only after stopword check
static char	*expand_heredoc(char *input, t_cmd *cmd)
{
	char	*tmp;

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

//helper, initializes a static value that indicates
//if SIGINT has been received
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

static void	heredoc_eof(t_cmd *cmd, char *input, int i)
{
	if (!input)
		printf(HEREDOC_WARN, cmd->here[i]);
	input = free_ptr(input);
	cmd->here_file = free_ptr(cmd->here_file);
}

void	heredoc_loop(t_cmd *cmd, int i, int fd, char *input)
{
	while (*(check_sigint()) != 1)
	{
		input = readline("> ");
		if (*(check_sigint()) == 1)
			empty_file(cmd);
		if (!(*(check_sigint())) && i == cmd->num[HERE] - 1)
		{
			if (!input || ft_strcmp(input, cmd->here[i]))
			{
				heredoc_eof(cmd, input, i);
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
		else if (input && ft_strcmp(input, cmd->here[i]))
			i++;
		input = free_ptr(input);
	}
}

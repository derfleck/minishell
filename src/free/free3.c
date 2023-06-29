/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:35:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/29 12:35:36 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	perror_shell_no_env(char *message, t_shell *sh)
{
	if (sh)
		free_shell(sh);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	exit (1);
}

void	perror_cmd_not_found(char *cmd, t_shell *sh)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	if (sh)
		free_shell(sh);
	g_stat = 127;
	exit(127);
}

void	perror_env_too_big(char *cmd, t_shell *sh, t_env **head)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!ft_strncmp("env", cmd, 3))
		ft_putstr_fd("/usr/bin/env", STDERR_FILENO);
	else
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Argument list too long\n", STDERR_FILENO);
	if (head)
		*head = free_env_list(head);
	if (sh)
		sh = free_shell(sh);
	exit(126);
}

int	perror_return_one(char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	g_stat = 1;
	return (g_stat);
}

void	free_sh_and_env(t_shell *sh, t_env **head)
{
	if (head != NULL)
		*head = free_env_list(head);
	if (sh != NULL)
		sh = free_shell(sh);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:33:31 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/29 12:33:42 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	err_mess_helper(int mode, char *path)
{
	if (mode == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(path);
		g_stat = 127;
	}
	else if (mode == 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		g_stat = 126;
	}
	else if (mode == 3)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(path);
		g_stat = 126;
	}
}

//checks if a path is a file or directory
//prints error and exits with 126 when directory
int	check_file_dir(char *path, t_shell *sh, t_env **head)
{
	struct stat	st;
	int			suc;

	suc = stat(path, &st);
	if (suc == -1)
		err_mess_helper(1, path);
	if (suc == 0 && S_ISREG(st.st_mode) && access(path, F_OK | X_OK) == 0)
		return (1);
	else if (suc == 0 && S_ISDIR(st.st_mode))
		err_mess_helper(2, path);
	else if (suc == 0 && access(path, F_OK | X_OK) != 0)
		err_mess_helper(3, path);
	free_sh_and_env(sh, head);
	exit(g_stat);
}

#include "../../inc/minishell.h"

/* Checks the first arg of the input for the correct command and sends
the rest of the args towards the right builtin */
void	builtin_pathfinder(t_env **env, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "pwd"))
		builtin_pwd();
	else if (ft_strcmp(cmd->cmd, "env"))
		print_env(env);
	else if (ft_strcmp(cmd->cmd, "test env"))
		env_tester("USER", env);
	else if (!ft_strncmp(cmd->cmd, "cd", 2))
		builtin_cd(cmd->arg, env);
	else if (!ft_strncmp(cmd->cmd, "export", 6))
		builtin_export(cmd->arg, env);
	else if (!ft_strncmp(cmd->cmd, "unset", 5))
		builtin_unset(cmd->arg, env);
	else
		printf("%s\n", cmd->cmd);
	// if (cmd->cmd)
	// 	free(cmd->cmd);
}

/* gets the current working directory and prints it on the screen */
void	builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	free(buf);
	g_stat = 0;
}

/* Counts how many arguments are in the token to deal with */
int	helper_get_arg_count(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
#include "../../inc/minishell.h"

/* Checks the first arg of the input for the correct command and sends
the rest of the args towards the right builtin */
void	builtin_pathfinder(t_env **env, char *input)
{
	if (ft_strcmp(input, "pwd"))
		builtin_pwd();
	else if (ft_strcmp(input, "env"))
		print_env(env);
	else if (ft_strcmp(input, "test env"))
		env_tester("USER", env);
	else if (!ft_strncmp(input, "cd", 2))
		builtin_cd(input, env);
	else if (!ft_strncmp(input, "export", 6))
		builtin_export(input, env);
	else if (!ft_strncmp(input, "unset", 5))
		builtin_unset(input, env);
	else
		printf("%s\n", input);
	if (input)
		free(input);
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

#include "../../inc/minishell.h"

void	builtin_echo(char **args, t_env **head)
{
	int	flag;

	flag = look_for_nflag(args[0])
	while (args[i])
	{
???
	}
	if (flag == 0)
		write(1, "\n", 1);
	g_status = 0;
}

/* iterates trough string to see if it is -n or -nnnn and nothing else */
static int	look_for_nflag(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[0] != '-' && str[i] != 'n')
			return (0);
	}
	return (1);
}

#include "../../inc/minishell.h"

/* iterates trough string to see if it is -n or -nnnn and nothing else
returns -1 if no args(str is NULL)
returns 1 if flag is valid,
returns 0 if flag is not valid  */
static int	look_for_nflag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0' || str[i] != '-' || \
	(str[i] == '-' && str[1] == '\0'))
		return (0);
	while (str[++i])
	{
		if (str[0] != '-' || str[i] != 'n')
			return (0);
	}
	return (1);
}

// do we need env here?
int	builtin_echo(char **args, t_env *head)
{
	int	flag;
	int	i;

	if (!args[0])
	{
		write(1, "\n", 1);
		return (0);
	}
	(void)head;
	i = -1;
	flag = look_for_nflag(args[0]);
	if (flag == 1)
		i++;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
	g_stat = 0;
	return (g_stat);
}

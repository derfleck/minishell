#include "../../inc/minishell.h"

static int	exit_stat_valid(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!ft_isnum(str[i]))
			return (0);
	}
	return (1);
}

static void	exit_helper(t_shell *sh, t_env **head, int err)
{
	if (head != NULL)
		head = free_env_list(head);
	if (sh != NULL)
		sh = free_shell(sh);
	exit(err);
}

/* Exits parent process */
static void	exit_parent(t_shell *sh, char **args, t_env **head, int argc)
{
	(void)head;
	if (argc == 1)
	{
		if (exit_stat_valid(args[0]))
			exit_helper(sh, head, (unsigned char)ft_atoi(args[0]));
		else
		{
			ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit_helper(sh, head, 2);
		}
	}
	if (argc == 0)
		exit_helper(sh, head, 0);
}

/* Based on process lvl it terminates a process 
Make sure to know if parent or child process is being terminated
ONLY: if (process == PARENT) later have child process too!! */
int	builtin_exit(t_shell *sh, char **args, t_env **env, int process)
{
	int	argc;

	argc = helper_get_arg_count(args);
	ft_putendl_fd("exit", STDERR_FILENO);
	if (argc == 0 || argc == 1)
		exit_parent(sh, args, env, argc);
	if (argc > 1 && process != 0)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_stat = 1;
		return (g_stat);
	}
	return (g_stat);
}

#include "../../inc/minishell.h"

/* Based on process lvl it terminates a process 
Make sure to know if parent or child process is being terminated
ONLY: if (process == PARENT) later have child process too!! */
int	builtin_exit(char **args, t_env *env, int process)
{
	int	argc;

	argc = helper_get_arg_count(args);
	ft_putendl_fd("exit", STDERR_FILENO);
	if (argc == 0 || argc == 1)
		exit_parent(args, env, argc);
	if (argc > 1 && process != 0)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	exit_stat_valid(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isnum(str[i]))
			return (0);
	}
	return (1);
}

/* Exits parent process */
void	exit_parent(char **args, t_env *head, int argc)
{
	(void)head;
	if (argc == 1)
	{
		free_env_list(head);
		// free_cmd_structs(cmd);
		if (exit_stat_valid(args[0]))
		{
			g_stat = (unsigned char)ft_atoi(args[0]);
			exit(g_stat);
		}
		else
		{
			ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit (2);
		}
	}
	if (argc == 0)
	{
		free_env_list(head);
		// free_cmd_structs(cmd);
		exit(0);
	}
}

/* Frees totality of env list */
void	*free_env_list(t_env *head)
{
	t_env	*node;

	if (head == NULL)
		return (NULL);
	node = head;
	while (node)
		node = free_env_node(node);
	if (head)
		head = NULL;
	return (NULL);
}

/* Frees a single env node */
void	*free_env_node(t_env *node)
{
	t_env	*tmp;

	if (!node)
		return (NULL);
	free_ptr(node->key_value);
	tmp = node->next;
	free_ptr(node);
	return (tmp);
}

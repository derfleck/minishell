#include "../../inc/minishell.h"

/* Based on process lvl it terminates a process 
Make sure to know if parent or child process is being terminated
ONLY: if (process == PARENT) later have child process too!! */
int	builtin_exit(t_cmd *cmd, t_env **env, int process)
{
	int	argc;

	argc = helper_get_arg_count(cmd->arg);
	(void)process;
	ft_putendl_fd("exit", 2);
	if (argc == 1)
		exit_parent(env, argc);
	if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	return (0);
}

/* Exits parent process */
void	exit_parent(t_env **head, int argc)
{
	if (argc == 1)
	{
		head = free_env_list(head);
		// cmd = free_cmd_structs(cmd);
		exit(0);
	}

}

/* Frees totality of env list */
void	*free_env_list(t_env **head)
{
	t_env	*node;

	if (head == NULL)
		return (NULL);
	while (head)
	{
		node = (*head)->next;
		head = free_env_node(*head);
		head = &node;
	}
	return (NULL);
}

/* Frees a single env node */
void	*free_env_node(t_env *node)
{
	if (!node)
		return (NULL);
	free_ptr(node->key_value);
	free_ptr(node);
	return (NULL);
}
#include "../../inc/minishell.h"

/* gets the current working directory and prints it on the screen */
int	builtin_pwd(t_env *head)
{
	char	*buf;

	g_stat = 0;
	(void)head;
	buf = getcwd(NULL, 0);
	if (buf)
	{
		printf("%s\n", buf);
		free_ptr(buf);
	}
	else
		g_stat = 1;
	return (g_stat);
}

/* prints the environment line by line */
int	builtin_env(t_env *env, char **args)
{
	t_env	*node;

	g_stat = 0;
	if (args && args[0])
	{
		g_stat = 127;
		ft_putendl_fd("minishell: env: too many arguments", STDERR_FILENO);
		return (g_stat);
	}
	node = env;
	while (node != NULL)
	{
		ft_putendl_fd(node->key_value, STDOUT_FILENO);
		node = node->next;
	}
	return (g_stat);
}

static void	builtin_unset_helper(char *str)
{
	ft_putstr_fd("Minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_stat = 1;
}

/* removes node - just the one received!!!*/
static void	remove_node(t_env **head, t_env *node)
{
	t_env	*temp;
	t_env	*prev;

	if (*head == NULL || !node)
		return ;
	prev = NULL;
	temp = *head;
	while (temp->key_value != node->key_value)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	if (prev == NULL)
		*head = (*head)->next;
	else
		prev->next = temp->next;
	free_ptr(temp->key_value);
	free_ptr(temp);
}
/* removes existing env variable, 
writes bash: unset: `STR': not a valid identifier if not found 
Unsetting a variable or function that was not previously set
shall not be considered an error and does not cause the shell to abort. */
int	builtin_unset(char **args, t_env **env)
{
	t_env	*node;
	int		i;

	i = -1;
	g_stat = 0;
	if (!args || !args[0])
		return (g_stat);
	while (args[++i])
	{
		if (key_validity_check(args[i]) != 1)
			builtin_unset_helper(args[i]);
		else
		{
			node = find_env_node(*env, args[i]);
			if (node == NULL)
				continue ;
			else if (ft_strcmp(args[i], "SHLVL"))
				reset_shlvl(env);
			else
				remove_node(env, node);
		}
	}
	return (g_stat);
}

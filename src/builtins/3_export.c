#include "../../inc/minishell.h"

/* Checks for an arg coming in without value OR (=)
--> if true, and key is valid, export should just return 
--> if true, and key is invalid, export should return 1 */
static int	export_isequal(char *arg, t_env *env)
{
	int		i;
	char	*str;

	str = split_env_key(arg, env);
	i = -1;
	if (!key_validity_check(str))
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_stat = 1;
		return (0);
	}
	free_ptr(str);
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			if (arg[i + 1] == '\0')
				return (1);
			else
				return (1);
		}
	}
	return (0);
}

/* Helper for export: in case of an arg like this: XXX+=555
where '+' is accepted as appending the string if exists - or
creating XXX=555 as new env variable */
static void	export_append_helper(char *key, char *str, t_env **env)
{
	char	*realkey;
	char	*realkey2;
	t_env	*node;

	realkey = ft_strtrim(key, "+");
	if (!realkey)
		perror_exit("Malloc failed\n");
	free_ptr(key);
	node = find_env_node(*env, realkey);
	if (node == NULL)
	{
		realkey2 = ft_strjoin(realkey, "=");
		free_ptr(realkey);
		node = create_node(ft_strjoin(realkey2, split_env_value(str)), *env);
		add_node_to_list(env, node);
	}	
	else
		append_node_value(node, split_env_value(str), env);
	free_ptr(realkey);
}

static void	builtin_export_helper(char *arg, t_env **env)
{
	t_env	*node;
	char	*key;

	if (!export_isequal(arg, *env))
		return ;
	key = split_env_key(arg, *env);
	if (key_validity_check(key) == -1)
	{
		export_append_helper(key, arg, env);
		return ;
	}
	node = find_env_node(*env, key);
	if (node == NULL)
	{
		node = create_node(arg, *env);
		add_node_to_list(env, node);
	}
	else
	{
		if (key_validity_check(key) == 1)
			replace_node_value(node, split_env_value(arg), env);
	}
	free_ptr(key);
	return ;
}

/* takes a 2d array of strs as argument after export command.
Checks if key is valid, then tries to find node in env,
 if not found it creates it. If found, it replaces
value with new value or nothing if nothing is specified
Can also append with KEY+=xy.
TODO: if no args?? declare -x $(env_var) shit 
-> no cause in manual its undefined behavior */
int	builtin_export(char **args, t_env **env)
{
	int		i;

	g_stat = 0;
	i = -1;
	if (!args || !args[0])
		return (g_stat);
	while (args[++i])
	{
		builtin_export_helper(args[i], env);
	}
	return (g_stat);
}

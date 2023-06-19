#include "../../inc/minishell.h"

/* Checks for an arg coming in without value OR (=)
--> if 1, and key is valid, export should just return */
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
	}
	free_ptr(str);
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			if (arg[i + 1] == '\0')
				return (0);
			else
				return (0);
		}
	}
	g_stat = 1;
	return (1);
}

/* Helper for export: in case of an arg like this: XXX+=555
where '+' is accepted as appending the string if exists - or
creating XXX=555 as new env variable */
static void	export_append_helper(char *key, char *str, t_env *env)
{
	char	*realkey;
	t_env	*node;

	realkey = ft_strtrim(key, "+");
	free_ptr(key);
	if (!realkey)
		perror_exit("Malloc failed\n");
	node = find_env_node(env, realkey);
	if (node == NULL)
	{
		realkey = ft_strjoin(realkey, "="); //malloc protect?
		node = create_node(ft_strjoin(realkey, split_env_value(str)), env);
		add_node_to_list(env, node);
	}	
	else
		append_node_value(node, split_env_value(str), env);
	free_ptr(realkey);
}

/* takes a str as argument after export command. tries to find
node in env, if not found it creates it. If found, it replaces
value with new value or nothing if nothing is specified
TODO: if no args?? declare -x $(env_var) shit */
int	builtin_export(char **args, t_env *env)
{
	t_env	*node;
	char	*key;
	int		i;

	g_stat = 0;
	i = -1;
	if (!args || !args[0])
		return (g_stat);
	while (args[++i])
	{
		if (export_isequal(args[i], env))
			return (g_stat);
		key = split_env_key(args[i], env);
		if (key_validity_check(key) == -1)
		{
			export_append_helper(key, args[i], env);
			return (g_stat);
		}
		node = find_env_node(env, key);
		if (node == NULL)
		{
			node = create_node(args[i], env);
			add_node_to_list(env, node);
		}
		else
		{
			if (key_validity_check(key) == 1)
				replace_node_value(node, split_env_value(args[i]), env);
		}
		free(key);
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

/* removes existing env variable, 
writes bash: unset: `STR': not a valid identifier if not found 
Unsetting a variable or function that was not previously set
shall not be considered an error and does not cause the shell to abort.
TODO: multiple KEYs to unset in one command */
int	builtin_unset(char **args, t_env *env)
{
	t_env	*node;

	g_stat = 0;
	if (!args || !args[0])
		return (g_stat);
	if (key_validity_check(args[0]) != 1)
		builtin_unset_helper(args[0]);
	else
	{
		node = find_env_node(env, args[0]);
		if (node == NULL)
			return (g_stat);
		else if (ft_strcmp(args[0], "SHLVL"))
			return (g_stat);
		else
			remove_node(env, args[0]);
	}
	return (g_stat);
}

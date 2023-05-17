#include "../../inc/minishell.h"

/* takes a str as argument after export command. tries to find
node in env, if not found it creates it. If found, it replaces
value with new value or nothing if nothing is specified
TODO: no incoming "=" ??? 
TODO: remove split, check input from Parser */
void	builtin_export(char *str, t_env **env)
{
	t_env	*node;
	char	**args;
	char	*key;

	if (!str)
		return ;
	args = ft_split(str, ' ');
	if (!args)
		perror_exit("Malloc failed\n");
	key = split_env_key(args[1]);
	if (key_validity_check(key) == -1)
	{
		export_append_helper(key, args[1], env);
		return ;
	}
	node = find_env_node(env, key);
	if (node == NULL)
	{
		node = create_node(str);
		add_node_to_list(env, node);
	}
	else
	{
		if (key_validity_check(key) == 1)
			replace_node_value(node, split_env_value(args[1]));
	}
	free(key);
}

/* Helper for export: in case of an arg like this: XXX+=555
where '+' is accepted as appending the string if exists - or
creating XXX=555 as new env variable */
void	export_append_helper(char *key, char *str, t_env **env)
{
	char	*realkey;
	t_env	*node;

	realkey = ft_strtrim(key, "+");
	free (key);
	if (!realkey)
		perror_exit("Malloc failed\n");
	node = find_env_node(env, realkey);
	if (node == NULL)
	{
		realkey = ft_strjoin(realkey, "=");
		node = create_node(ft_strjoin(realkey, split_env_value(str)));
		add_node_to_list(env, node);
	}	
	else
		append_node_value(node, split_env_value(str));
	free (realkey);
}

/* removes existing env variable, 
writes bash: unset: `STR': not a valid identifier if not found 
Unsetting a variable or function that was not previously set
shall not be considered an error and does not cause the shell to abort.*/
void	builtin_unset(char *str, t_env **env)
{
	t_env	*node;
	char	**args;

	if (!str)
		return ;
	args = ft_split(str, ' ');
	if (key_validity_check(args[1]) != 1)
	{
		printf("Minishell: unset: `%s': not a valid identifier\n", args[1]);
		g_stat = 1;
	}
	else
	{
		node = find_env_node(env, args[1]);
		if (node == NULL)
		{
			g_stat = 0;
			return ;
		}
		else
			remove_node(env, args[1]);
	}
	g_stat = 0;
}

#include "../../inc/minishell.h"

/* takes a str as argument after export command. tries to find node in env,
if not found it creates it. If found, it replaces value with new value or nothing if nothing is specified
TODO: no incoming "=" ??? */
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
		node = create_node(args[1]);
		add_node_to_list(env, node);
	}
	else
	{
		if (key_validity_check(key) == 1)
			replace_node_value(node, split_env_value(args[1]));
	}
	free(key);
}
/* Helper for export: in case of an arg like this: XXX+=555 where '+' is accepted
as appending the string if exists - or creating XXX=555 as new env variable */
void	export_append_helper(char *key, char *str, t_env **env)
{
	char 	*realkey;
	t_env	*node;

	realkey = ft_strtrim(key, "+");
	free (key);
	if (!realkey)
		perror_exit("Malloc failed\n");
	node = find_env_node(env, realkey);
	if (node == NULL)
	{
		node = create_node(str); // remove + (use realkey)
		add_node_to_list(env, node);
	}	
	else
		append_node_value(node, split_env_value(str));
	free (realkey);
}
/* removes env variable,  */
void	builtin_unset(char *str, t_env **env)
{
	t_env	*node;
	char	**args;

	if (!str)
		return ;
	args = ft_split(str, ' ');
	node = find_env_node(env, args[1]);
	if (node == NULL)
		return ; //Unsetting a variable or function that was not previously set shall not be considered an  error and does not cause the shell to abort.
	else
		remove_node(env, args[1]);
}

int	builtin_cd(char *input, t_env **env)
{
	int		i;
	char	**args;
	char	*oldpath;
	char	*home;
	t_env	*node;

	i = -1;
	oldpath = getcwd(NULL, 0);
	args = ft_split(input, ' '); //will not be needed if path comes in
	if (!args)
		perror_exit("cd - split failed\n");
	if (args[2])
	{
		printf("Minishell: cd:   : Too many arguments\n");
		return (0); //free?
	}
	if (!args[1] || (args[1][0] == '~' && args[1][1] == '\0'))
	{
		node = find_env_node(env, "HOME");
		home = split_env_value(node->key_value);
		if (chdir(home) != 0)
			printf("Minishell: cd: %s: No such file or directory", args[1]);
	}
	else if (args[1][0] == '\0')
		//return prompt!!
		return (0);
	else if (chdir(args[1]) != 0)
	{
		printf("Minishell: cd: %s", args[1]);
		printf(": No such file or directory\n");
		return (0);
	}
	update_pwds(env, oldpath);
	return (1);
}
//TODO check how args come in from parser

void	update_pwds(t_env **env, char *oldpath)
{
	t_env	*node1;
	t_env	*node2;
	char	*newpath;
	char	*oldpwd;

	newpath = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", oldpath);
	if (oldpwd == NULL)
		perror_exit("Malloc failed\n");
	node1 = find_env_node(env, "PWD");
	node2 = find_env_node(env, "OLDPWD");
	if (node2 == NULL)
		node2 = create_node(oldpwd);
	else
		replace_node_value(node2, oldpath);
	free(oldpwd);
	free(oldpath);
	if (newpath == NULL)
	{
		if (chdir("/") != 0)
			perror_exit("cd: chdir to home went wrong\n");
	}
	else
		replace_node_value(node1, newpath);
	free(newpath);
}

#include "../../inc/minishell.h"

/* changes the current working directory and updates env */
//TODO check how args come in from parser
void	builtin_cd(char **args, t_env *env)
{
	char	*oldpath;
	int		argc;

	argc = helper_get_arg_count(args);
	oldpath = getcwd(NULL, 0);
	if (argc > 1)
	{
		printf("Minishell: cd:   : Too many arguments\n");
		return ;
	}	
	if (!args[0] || (args[0][0] == '~' && args[0][1] == '\0'))
		cd_go_home(env, args[0]);
	else if (args[0][0] == '\0')
		return ;
	else if (chdir(args[0]) != 0)
	{
		printf("Minishell: cd: %s", args[0]);
		printf(": No such file or directory\n");
		return ;
	}
	update_pwds(env, oldpath);
}

/* Helper for cd to change working directory to HOME based on env */
void	cd_go_home(t_env *env, char *str)
{
	char	*home;
	t_env	*node;

	node = find_env_node(env, "HOME");
	home = split_env_value(node->key_value);
	if (chdir(home) != 0)
		printf("Minishell: cd: %s: No such file or directory", str);
}

/* updates env variables PWD and OLDPWD after cd was called */
void	update_pwds(t_env *env, char *oldpath)
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

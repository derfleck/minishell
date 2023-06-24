#include "../../inc/minishell.h"

/* updates env variables PWD and OLDPWD after cd was called */
static void	update_pwds(t_env **env, char *oldpath)
{
	t_env	*node1;
	t_env	*node2;
	char	*newpath;
	char	*oldpwd;

	newpath = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", oldpath);
	if (oldpwd == NULL)
		perror_exit("Malloc failed\n");
	node1 = find_env_node(*env, "PWD");
	node2 = find_env_node(*env, "OLDPWD");
	if (node2 == NULL)
		node2 = create_node(oldpwd, *env);
	else
		replace_node_value(node2, oldpath, env);
	oldpwd = free_ptr(oldpwd);
	oldpath = free_ptr(oldpath);
	if (newpath == NULL)
	{
		if (chdir("/") != 0)
			perror_exit("cd: chdir to home went wrong\n");
	}
	else
		replace_node_value(node1, newpath, env);
	newpath = free_ptr(newpath);
}

/* Counts how many arguments are in the array to deal with 
SETS G_STAT to NULL!   USED IN: cd, exit */
int	helper_get_arg_count(char **args)
{
	int	count;

	g_stat = 0;
	count = 0;
	while (args[count])
		count++;
	return (count);
}

/* changes the current working directory and updates env */
//TODO check how args come in from parser
int	builtin_cd(char **args, t_env **env)
{
	char	*oldpath;
	int		argc;

	argc = helper_get_arg_count(args);
	oldpath = getcwd(NULL, 0);
	if (argc > 1)
	{
		ft_putendl_fd("Minishell: cd:   : Too many arguments", STDERR_FILENO);
		g_stat = 1;
		oldpath = free_ptr(oldpath);
		return (g_stat);
	}
	else if (args[0][0] == '\0')
		return (g_stat);
	else if (chdir(args[0]) != 0)
	{
		ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_stat = 1;
		oldpath = free_ptr(oldpath);
		return (g_stat);
	}
	update_pwds(env, oldpath);
	return (g_stat);
}

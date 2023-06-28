#include "../../inc/minishell.h"

static t_env	*check_or_create(t_env **head, char *key, char *new_keyvalue)
{
	t_env	*node;

	node = find_env_node(*head, key);
	if (node == NULL)
	{
		node = create_node(new_keyvalue, *head);
		add_node_to_list(head, node);
	}
	new_keyvalue = free_ptr(new_keyvalue);
	return (node);
}

/* updates env variables PWD and OLDPWD after cd was called */
static void	update_pwds(t_env **env, char *oldpath)
{
	t_env	*node1;
	t_env	*node2;
	char	*newpath;
	char	*newpwd;
	char	*oldpwd;

	newpath = getcwd(NULL, 0);
	newpwd = ft_strjoin("PWD=", newpath);
	if (!newpwd)
		perror_exit_free_env("Malloc failed", *env);
	oldpwd = ft_strjoin("OLDPWD=", oldpath);
	if (!oldpwd)
		perror_exit_free_env("Malloc failed", *env);
	node1 = check_or_create(env, "PWD", newpwd);
	node2 = check_or_create(env, "OLDPWD", oldpwd);
	replace_node_value(node2, oldpath, env);
	oldpath = free_ptr(oldpath);
	if (newpath == NULL)
	{
		if (chdir("/") != 0)
			perror_exit_free_env("cd: chdir to home went wrong", *env);
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

static int	builtin_cd_nofileordirectory(char *str, char *oldpath)
{
	ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	oldpath = free_ptr(oldpath);
	g_stat = 1;
	return (g_stat);
}

/* changes the current working directory and updates env */
//TODO check how args come in from parser
int	builtin_cd(char **args, t_env **env)
{
	char	*oldpath;
	int		argc;

	argc = helper_get_arg_count(args);
	if (argc == 0)
	{
		oldpath = getcwd(NULL, 0);
		chdir("/");
		update_pwds(env, oldpath);
		return (g_stat);
	}
	else if (argc > 1)
	{
		ft_putendl_fd("Minishell: cd:   : Too many arguments", STDERR_FILENO);
		return (1);
	}
	else if (args[0][0] == '\0')
		return (0);
	oldpath = getcwd(NULL, 0);
	if (chdir(args[0]) != 0)
		return (builtin_cd_nofileordirectory(args[0], oldpath));
	update_pwds(env, oldpath);
	return (g_stat);
}

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
static int	update_pwds(t_env **env, char *oldpath)
{
	t_env	*node1;
	t_env	*node2;
	char	*newpath;
	char	*newpwd;
	char	*oldpwd;

	newpath = getcwd(NULL, 0);
	newpwd = ft_strjoin("PWD=", newpath);
	if (!newpwd)
		return (perror_return_one("Malloc failed"));
	oldpwd = ft_strjoin("OLDPWD=", oldpath);
	if (!oldpwd)
		return (perror_return_one("Malloc failed"));
	node1 = check_or_create(env, "PWD", newpwd);
	node2 = check_or_create(env, "OLDPWD", oldpwd);
	replace_node_value(node2, oldpath, env);
	oldpath = free_ptr(oldpath);
	replace_node_value(node1, newpath, env);
	newpath = free_ptr(newpath);
	return (0);
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

static int	bi_cd_helper1(t_env **env, char *arg)
{
	char	*oldpath;
	t_env	*node;

	oldpath = getcwd(NULL, 0);
	if (!oldpath)
		oldpath = ft_strdup("");
	if (arg && arg[0] == '-' && arg[1] == '\0')
	{
		node = find_env_node(*env, "OLDPWD");
		if (!node || !split_env_value(node->key_value))
		{
			ft_putendl_fd("Minishell: cd: OLDPWD not set", STDERR_FILENO);
			oldpath = free_ptr(oldpath);
			return (1);
		}
		else 
		{
			ft_putendl_fd(split_env_value(node->key_value), STDOUT_FILENO);
			return (export_minus_helper(split_env_value(node->key_value), env, oldpath));
		}
	}
	else if (chdir(arg) != 0)
		return (builtin_cd_nofileordirectory(arg, oldpath));
	update_pwds(env, oldpath);
	return (0);
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
	else if (argc == 1)
		g_stat = bi_cd_helper1(env, args[0]);
	else if (args[0][0] == '\0')
		return (0);
	return (g_stat);
}

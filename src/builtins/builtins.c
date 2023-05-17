#include "../../inc/minishell.h"

/* Checks the first arg of the input for the correct command and sends
the rest of the args towards the right builtin */
void	builtin_pathfinder(t_env **env, char *input)
{
	if (ft_strcmp(input, "pwd"))
		get_pwd();
	else if (ft_strcmp(input, "env"))
		print_env(env);
	else if (ft_strcmp(input, "test env"))
		env_tester("USER", env);
	else if (!ft_strncmp(input, "cd", 2))
		builtin_cd(input, env);
	else if (!ft_strncmp(input, "export", 6))
		builtin_export(input, env);
	else if (!ft_strncmp(input, "unset", 5))
		builtin_unset(input, env);
	else
		printf("%s\n", input);
	if (input)
		free(input);
}

/* changes the current working directory and updates env */
//TODO check how args come in from parser
void	builtin_cd(char *input, t_env **env)
{
	char	**args;
	char	*oldpath;

	oldpath = getcwd(NULL, 0);
	args = ft_split(input, ' ');
	if (!args)
		perror_exit("cd - split failed\n");
	if (args[1] && args[2])
	{
		printf("Minishell: cd:   : Too many arguments\n");
		return ;
	}	
	if (!args[1] || (args[1][0] == '~' && args[1][1] == '\0'))
		cd_go_home(env, args[1]);
	else if (args[1][0] == '\0')
		return ;
	else if (chdir(args[1]) != 0)
	{
		printf("Minishell: cd: %s", args[1]);
		printf(": No such file or directory\n");
		return ;
	}
	update_pwds(env, oldpath);
}

/* Helper for cd to change working directory to HOME based on env */
void	cd_go_home(t_env **env, char *str)
{
	char	*home;
	t_env	*node;

	node = find_env_node(env, "HOME");
	home = split_env_value(node->key_value);
	if (chdir(home) != 0)
		printf("Minishell: cd: %s: No such file or directory", str);
}

/* updates env variables PWD and OLDPWD after cd was called */
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

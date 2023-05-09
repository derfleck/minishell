#include "../../inc/minishell.h"

void	builtin_export(char *str)
{
	int	i;

	printf("%s", str);
	i = 0;
}

int	builtin_cd(char *input, t_env *env)
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
		perror("cd - split failed\n");
	if (args[2])
	{
		printf("Minishell: cd:   : Too many arguments\n");
		return (0); //free?
	}
	if (!args[1] || (args[1][0] == '~' && args[1][1] == '\0'))
	{
		node = find_env_node(&env, "HOME");
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

void	update_pwds(t_env *env, char *oldpath)
{
	t_env	*node1;
	t_env	*node2;
	char	*newpath;
	char	*oldpwd;

	newpath = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", oldpath);
	if (oldpwd == NULL)
		perror("Malloc failed\n");
	node1 = find_env_node(&env, "PWD");
	node2 = find_env_node(&env, "OLDPWD");
	if (node2 == NULL)
		node2 = create_node(oldpwd);
	else
		replace_node(node2, oldpath);
	free(oldpwd);
	free(oldpath);
	if (newpath == NULL)
	{
		if (chdir("/") != 0)
			perror("cd: chdir to home went wrong\n");
	}
	else
		replace_node(node1, newpath);
	free(newpath);
}

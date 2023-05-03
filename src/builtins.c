#include "../inc/minishell.h"

void	builtin_echo(char *str)
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

	i = -1;
	args = ft_split(input, ' ');
	if (!args)
		perror("cd - split failed\n");
	if (args[2])
	{
		printf("Minishell: cd:   : Too many arguments\n");
		return (0);
	}
	if (!args[1])
		chdir("/");
	if (args[1][0] == '\0')
		//return prompt!!
		return (0);
	oldpath = getcwd(NULL, 0);
	if (chdir(args[1]) != 0)
	{
		printf("Minishell: cd: %s", args[1]);
		printf(": No such file or directory\n");
		return (0);
	}
	update_pwd(env, oldpath);
	return (1);
}

void	update_pwd(t_env *env, char *oldpath)
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
		node2->key_value = oldpwd;
	free(oldpwd);
	free(oldpath);
	if (newpath == NULL)
	{
		if (chdir("/") != 0)
			perror("cd: chdir to home went wrong\n");
	}
	else
	{
		node1->key_value = ft_strjoin("PWD=", newpath);
		if (node1->key_value == NULL)
			perror("Malloc failed\n");
	}
	free(newpath);
}

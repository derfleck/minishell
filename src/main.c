#include "../inc/minishell.h"

int	g_stat = 0;

static int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

char	*prompt_line(void)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strjoin(getenv("USER"), "@minishell:");
	tmp2 = getcwd(NULL, 0);
	if (ft_strcmp(tmp2, getenv("HOME")))
	{
		free(tmp2);
		return (ft_strjoin(tmp, "~$"));
	}
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp3, "$");
	free(tmp3);
	return (tmp);
}

void	get_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	free(buf);
}

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	t_env	*env;

	t_env	node;
	char 	*key = "USER";

	(void)argc;
	(void)argv;
	env = init_env(envp);
	node = *find_env_node(&env, key);
	printf("%s\n", node.key_value);
	while (1)
	{
		s = readline(prompt_line());
		if (s == NULL)
			continue ;
		add_history(s);
		if (ft_strcmp(s, "pwd"))
			get_pwd();
		else if (ft_strcmp(s, "env"))
			print_env(env);
		else if (ft_strcmp(s, "key"))
		{
			printf("%s\n", node.key_value);
			key = split_env_key(node.key_value);
			printf("%s\n", key);
		}
		else if (ft_strcmp(s, "value"))
		{
			printf("%s\n", node.key_value);
			key = split_env_value(node.key_value);
			printf("%s\n", key);
		}
		else
			printf("%s\n", s);
		if (s)
			free(s);
	}
	return (0);
}

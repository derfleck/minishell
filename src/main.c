#include "../inc/minishell.h"

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

	(void)argc;
	(void)argv;
	env = init_env(envp);
	while (1)
	{
		s = readline(prompt_line());
		if (ft_strcmp(s, "pwd"))
			get_pwd();
		else if (ft_strcmp(s, "env"))
			print_env(env);
		else
			printf("%s\n", s);
		free(s);
	}
	return (0);
}


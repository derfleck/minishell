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
	if (!tmp)
		perror_exit("Malloc failed\n");
	tmp2 = getcwd(NULL, 0);
	if (ft_strcmp(tmp2, getenv("HOME")))
	{
		free(tmp2);
		return (ft_strjoin(tmp, "~$"));
	}
	tmp3 = ft_strjoin(tmp, tmp2);
	if (!tmp3)
		perror_exit("Malloc failed\n");
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp3, "$");
	if (!tmp)
		perror_exit("Malloc failed\n");
	free(tmp3);
	return (tmp);
}

void	get_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	free(buf);
	g_stat = 0;
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
		set_sigaction(PARENT);
		s = readline(prompt_line());
		if (s == NULL)
			return (write(2, "exit\n", 5));
		add_history(s);
		if (ft_strcmp(s, "pwd"))
			get_pwd();
		else if (ft_strcmp(s, "env"))
			print_env(env);
		else if (ft_strcmp(s, "test env"))
			env_tester("USER", &env);
		else if (!ft_strncmp(s, "cd", 2))
			builtin_cd(s, &env);
		else if (!ft_strncmp(s, "export", 6))
			builtin_export(s, &env);
		else if (!ft_strncmp(s, "unset", 5))
			builtin_unset(s, &env);
		else
			printf("%s\n", s);
		if (s)
			free(s);
	}
	return (0);
}

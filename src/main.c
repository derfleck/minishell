#include "../inc/minishell.h"

int	g_stat = 0;

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

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	t_env	*env;
	t_lexer	*lex;
	t_cmd	*cmd;

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
		lex = start_lexer(s);
		cmd = create_parse_list(lex);
		builtin_pathfinder(&env, cmd);
	}
	return (0);
}

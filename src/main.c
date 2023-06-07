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
		return (ft_strjoin(tmp, "~$ "));
	}
	tmp3 = ft_strjoin(tmp, tmp2);
	if (!tmp3)
		perror_exit("Malloc failed\n");
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp3, "$ ");
	if (!tmp)
		perror_exit("Malloc failed\n");
	free(tmp3);
	return (tmp);
}

char	*get_input()
{
	char	*line;
	char	*prompt;

	prompt = prompt_line();
	if (prompt == NULL)
		return (ft_strdup("exit"));
	line = readline(prompt);
	if (line == NULL)
		return (ft_strdup("exit"));
	else if (line[0] == 0)
		return (safe_free(line), safe_free(prompt));
	prompt = safe_free(prompt);
	return (line);
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
		s = get_input();
		if (s == NULL)
			continue ;
		lex = start_lexer(s);
		add_history(s);
		if (lex)
			cmd = create_parse_list(lex);
		if (cmd != NULL && env != NULL)
			init_shell(cmd, env);
	}
	return (0);
}

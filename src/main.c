#include "../inc/minishell.h"

int	g_stat = 0;


char	*prompt_line(t_env *head)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	t_env	*node;

	node = find_env_node(head, "USER");
	tmp = ft_strjoin(split_env_value(node->key_value), "@minishell:");
	if (!tmp)
		perror_exit_free_env("Malloc failed\n", head);
	tmp2 = getcwd(NULL, 0);
	if (ft_strcmp(tmp2, getenv("HOME")))
	{
		free(tmp2);
		return (ft_strjoin(tmp, "~$ "));
	}
	tmp3 = ft_strjoin(tmp, tmp2);
	if (!tmp3)
		perror_exit_free_env("Malloc failed\n", head);
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp3, "$ ");
	if (!tmp)
		perror_exit_free_env("Malloc failed\n", head);
	free(tmp3);
	return (tmp);
}

char	*get_input(t_env *head)
{
	char	*line;
	char	*prompt;

	prompt = prompt_line(head);
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
	lex = NULL;
	cmd = NULL;
	while (1)
	{
		set_sigaction(PARENT);
		s = get_input(env);
		if (s == NULL)
			continue ;
		add_history(s);
		lex = start_lexer(s);
		if (lex)
			expander_start(lex, env);
		if (lex)
			cmd = create_parse_list(lex);
		if (cmd != NULL && env != NULL)
			init_shell(s, cmd, &env);
	}
	return (0);
}

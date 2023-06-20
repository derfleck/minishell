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

char	*get_input(t_env *head)
{
	char	*line;
	char	*prompt;

	prompt = prompt_line(head);
	if (prompt == NULL)
		return (ft_strdup("exit"));
	line = readline(prompt);
	//rl_catch_signals = 0;
	//rl_done = 1;
	prompt = safe_free(prompt);
	if (line == NULL)
		return (ft_strdup("exit"));
	else if (line[0] == 0)
		return (safe_free(line));
	return (line);
}
//TODO: s wiederherstellen, aktuell nur trimmed string -> start_lexer
int	main(int argc, char **argv, char **envp)
{
	char	*s;
	t_env	*env;
	t_lexer	*lex;
	t_cmd	*cmd;

	if (argc > 1)
		printf("%s: no arguments allowed", argv[1]);
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
		lex = start_lexer(s, env);
		if (!lex)
			continue ;
		expander_start(lex, env);
		cmd = create_parse_list(lex);
		if (cmd != NULL && env != NULL)
			init_shell(s, cmd, env);
		//free(s);
	}
	return (0);
}

#include "../inc/minishell.h"

int	g_stat = 0;

static	char	*search_return_value(t_env *head, char *key)
{
	t_env	*node;
	char	*val;

	node = find_env_node(head, key);
	if (!node)
		return (NULL);
	val = split_env_value(node->key_value);
	return (val);
}

//expands current directory so only path after home is shown
static	char	*expand_home_prompt(t_env *head)
{
	char	*home;
	char	*cwd;
	char	*str;

	home = search_return_value(head, "HOME");
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		cwd = search_return_value(head, "PWD");
		if (cwd != NULL)
			cwd = ft_strdup(cwd);
	}
	if (cwd == NULL)
		cwd = ft_strdup(".");
	if (home && ft_strncmp(home, cwd, ft_strlen(home)) == 0 && \
		home[ft_strlen(home) - 1] != '/')
	{
		str = ft_strjoin("~", cwd + ft_strlen(home));
		if (!str)
			perror_exit_free_env("Malloc failed\n", head);
		free(cwd);
		return (str);
	}
	else
		return (cwd);
}

//constructs the prompt line from the copy of the environment variables
static char	*prompt_line(t_env *head)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	t_env	*node;

	node = find_env_node(head, "USER");
	tmp = ft_strjoin("\001\e\033[36m\002", split_env_value(node->key_value));
	if (!tmp)
		perror_exit_free_env("Malloc failed1\n", head);
	tmp2 = ft_strjoin(tmp, "@minishell");
	if (!tmp2)
		perror_exit_free_env("Malloc failed\n", head);
	free(tmp);
	tmp = tmp2;
	tmp2 = expand_home_prompt(head);
	tmp3 = safe_join(tmp, tmp2, head);
	tmp = ft_strjoin(tmp3, "$ \001\e[0m\002");
	if (!tmp)
		perror_exit_free_env("Malloc failed\n", head);
	free(tmp3);
	return (tmp);
}

static char	*get_input(t_env *head)
{
	char	*line;
	char	*prompt;

	prompt = prompt_line(head);
	if (prompt == NULL)
		return (ft_strdup("exit"));
	line = readline(prompt);
	prompt = free_ptr(prompt);
	if (line == NULL)
		return (ft_strdup("exit"));
	else if (line[0] == 0)
		return (free_ptr(line));
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	t_env	*env;
	t_lexer	*lex;
	t_cmd	*cmd;

	if (argc > 1)
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
		lex = start_lexer(s, env);
		if (!lex)
			continue ;
		expander_start(lex, env);
		cmd = create_parse_list(lex, env);
		init_shell(s, cmd, &env);
	}
	return (0);
}

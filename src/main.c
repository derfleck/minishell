#include "../inc/minishell.h"

int	g_stat = 0;

//expands current directory so only path after home is shown
static	char *expand_home_prompt(t_env *head)
{
	t_env	*node;
	char	*home;
	char	*cwd;
	char	*str;

	node = find_env_node(head, "HOME");
	home = split_env_value(node->key_value);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror_exit_free_env("Malloc failed\n", head);
	if (ft_strncmp(home, cwd, ft_strlen(home)) == 0 && \
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

static char *safe_join(char *s1, char *s2, t_env *head)
{
	char *ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		perror_exit_free_env("Malloc failed\n", head);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ret);
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
		perror_exit_free_env("Malloc failed\n", head);
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
	prompt = safe_free(prompt);
	if (line == NULL)
		return (ft_strdup("exit"));
	else if (line[0] == 0)
		return (safe_free(line));
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
		cmd = create_parse_list(lex);
		if (cmd != NULL && env != NULL)
			init_shell(s, cmd, &env);
	}
	return (0);
}

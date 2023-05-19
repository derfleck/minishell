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
	g_stat = 0;
}

void	print_lexer(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		printf("%i: %s (%i)\n", tmp->i, tmp->str, tmp->token);
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		printf("Command group %s: \narguments:", tmp->cmd);
		while (tmp->arg[i])
			printf("%s ", tmp->arg[i++]);
		i = 0;
		printf("\ninput: ");
		while (tmp->in->input[i])
			printf("%s ", tmp->in->input[i++]);
		i = 0;
		printf("\noutput: ");
		while (tmp->out->output[i])
			printf("%s ", tmp->out->output[i++]);
		i = 0;
		printf("\nappend: ");
		while (tmp->out->append[i])
			printf("%s ", tmp->out->append[i++]);
		i = 0;
		printf("\nhere: ");
		while (tmp->in->here[i])
			printf("%s ", tmp->in->here[i++]);
		if (tmp->in->last)
			printf("\nlast input: %s\n",  tmp->in->last->next->str);
		if (tmp->out->last)
			printf("last output: %s\n", tmp->out->last->next->str);
		printf("\n");
		tmp = tmp->next;
	}
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
		lex = start_lexer(s);
		cmd = create_parse_list(lex);
		if (cmd)
			print_cmd(cmd);
		if (s == NULL)
			return (write(2, "exit\n", 5));
		add_history(s);
		if (ft_strcmp(s, "pwd"))
			get_pwd();
		else if (ft_strcmp(s, "env"))
			print_env(env);
		else if (ft_strcmp(s, "test env"))
			env_tester("USER", &env);
		else
			printf("%s\n", s);
		if (s)
			free(s);
	}
	return (0);
}

#include "../../inc/minishell.h"

void	perror_exit_2(char *message, t_shell *sh, t_env **env, int mode)
{
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	if (sh)
		sh = free_shell(sh);
	g_stat = 2;
	if (mode == CHILD)
	{
		if (env)
			*env = free_env_list(env);
		exit (2);
	}
}

void	perror_lexer(char *message, char *s, t_env *env, t_lexer *lex)
{
	if (s)
		s = free_ptr(s);
	if (env)
		env = free_env_list(&env);
	if (lex)
		lex = free_lex(lex);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	exit (1);
}

void	perror_cmd(char *message, t_cmd *cmd, t_env *head)
{
	if (head)
		head = free_env_list(&head);
	if (cmd)
		cmd = free_cmd(cmd);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	exit (1);
}

void	perror_shell(char *message, t_shell *sh)
{
	if (sh->head)
		sh->head = free_env_list(&sh->head);
	if (sh)
		sh = free_shell(sh);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	exit (1);
}

void	perror_heredoc(t_shell *sh)
{
	t_cmd	*tmp;

	tmp = sh->cmd_start;
	while (tmp)
	{
		unlink_heredoc(tmp);
		tmp = tmp->next;
	}
}

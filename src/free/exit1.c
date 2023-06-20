#include "../../inc/minishell.h"

void	*free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

void	perror_exit(char *message)
{
	if (message)
		perror(message);
	exit (1);
}

void	perror_lexer(char *message, char *s, t_env *env, t_lexer *lex)
{
	if (s)
		free(s);
	if (env)
		free_env_list(env);
	if (lex)
		lex = free_lex(lex);
	if (message)
		ft_putendl_fd(message, STDOUT_FILENO);
	exit (1);
}

void	perror_cmd(char *message, t_cmd *cmd, t_env *head)
{
	if (head)
		free_env_list(head);
	if (cmd)
		free_cmd(cmd);
	if (message)
		ft_putendl_fd(message, STDOUT_FILENO);
	exit (1);
}

void	perror_shell(char *message, t_shell *sh)
{
	if (sh->head)
		free_env_list(sh->head);
	if (sh)
		free_shell(sh);
	if (message)
		ft_putendl_fd(message, STDOUT_FILENO);
	exit (1);
}

void	perror_shell_no_env(char *message, t_shell *sh)
{
	if (sh)
		free_shell(sh);
	if (message)
		ft_putendl_fd(message, STDOUT_FILENO);
	exit (1);
}

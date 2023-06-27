#include "../../inc/minishell.h"

void	*free_ptr(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

void	*free_charray(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		arr[i] = free_ptr(arr[i]);
		i++;
	}
	if (arr != NULL)
		arr = free_ptr(arr);
	return (NULL);
}

void	perror_exit_free_env(char *message, t_env *head)
{
	if (message != NULL)
		perror(message);
	if (head != NULL)
		head = free_env_list(&head);
	exit (1);
}

//TODO: needs to free everything!!!
void	perror_exit(char *message)
{
	if (message != NULL)
		perror(message);
	//free_env_list(head);
	exit (1);
}

void	perror_exit_2(char *message, t_shell *sh, t_env **env, int mode)
{
	if (message != NULL)
		ft_putstr_fd(message, STDERR_FILENO);
	if (sh != NULL)
		sh = free_shell(sh);
	g_stat = 2;
	if (mode == CHILD)
	{
		if (env != NULL)
			env = free_env_list(env);
		exit (2);
	}
}

void	perror_lexer(char *message, char *s, t_env *env, t_lexer *lex)
{
	if (s != NULL)
		s = free_ptr(s);
	if (env != NULL)
		env = free_env_list(&env);
	if (lex != NULL)
		lex = free_lex(lex);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	exit (1);
}

void	perror_cmd(char *message, t_cmd *cmd, t_env *head)
{
	if (head != NULL)
		head = free_env_list(&head);
	if (cmd != NULL)
		cmd = free_cmd(cmd);
	if (message != NULL)
		ft_putendl_fd(message, STDERR_FILENO);
	exit (1);
}

void	perror_shell(char *message, t_shell *sh)
{
	if (sh->head != NULL)
		sh->head = free_env_list(&sh->head);
	if (sh != NULL)
		sh = free_shell(sh);
	if (message != NULL)
		ft_putendl_fd(message, STDERR_FILENO);
	exit (1);
}

void	perror_shell_no_env(char *message, t_shell *sh)
{
	if (sh != NULL)
		sh = free_shell(sh);
	if (message != NULL)
		ft_putendl_fd(message, STDERR_FILENO);
	exit (1);
}

void	perror_cmd_not_found(char *cmd, t_shell *sh)
{
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	if (sh != NULL)
		sh = free_shell(sh);
	g_stat = 127;
	exit(127);
}

void	perror_env_too_big(char *cmd, t_shell *sh, t_env **head)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!ft_strncmp("env", cmd, 3))
		ft_putstr_fd("/usr/bin/env", STDERR_FILENO);
	else
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Argument list too long\n", STDERR_FILENO);
	if (head != NULL)
		head = free_env_list(head);
	if (sh != NULL)
		sh = free_shell(sh);
	exit(126);
}

/* static helper of free_env_list
Frees a single env node */
static void	*free_env_node(t_env *node)
{
	t_env	*tmp;

	if (!node)
		return (NULL);
	node->key_value = free_ptr(node->key_value);
	tmp = node->next;
	node = free_ptr(node);
	return (tmp);
}

/* Frees totality of env list */
void	*free_env_list(t_env **head)
{
	t_env	*node;

	if (head == NULL)
		return (NULL);
	node = *head;
	while (node)
		node = free_env_node(node);
	head = NULL;
	return (NULL);
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
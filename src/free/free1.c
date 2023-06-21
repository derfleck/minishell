#include "../../inc/minishell.h"

void	*free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

void	perror_exit_free_env(char *message, t_env *head)
{
	if (message)
		perror(message);
	free_env_list(&head);
	exit (1);
}

//TODO: needs to free everything!!!
void	perror_exit(char *message)
{
	if (message)
		perror(message);
	//free_env_list(head);
	exit (1);
}

void	perror_lexer(char *message, char *s, t_env *env, t_lexer *lex)
{
	if (s)
		free(s);
	if (env)
		free_env_list(&env);
	if (lex)
		lex = free_lex(lex);
	if (message)
		ft_putendl_fd(message, STDOUT_FILENO);
	exit (1);
}

void	perror_cmd(char *message, t_cmd *cmd, t_env *head)
{
	if (head)
		free_env_list(&head);
	if (cmd)
		free_cmd(cmd);
	if (message)
		ft_putendl_fd(message, STDOUT_FILENO);
	exit (1);
}

void	perror_shell(char *message, t_shell *sh)
{
	if (sh->head)
		free_env_list(&sh->head);
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
/* static helper of free_env_list
Frees a single env node */
static void	*free_env_node(t_env *node)
{
	t_env	*tmp;

	if (!node)
		return (NULL);
	free_ptr(node->key_value);
	tmp = node->next;
	free_ptr(node);
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


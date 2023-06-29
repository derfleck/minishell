#include "../../inc/minishell.h"

/* It is important to check if envp is NULL before accessing it
in order to avoid segmentation faults and other errors. 
Need cpy of env because maintaining the original through reallocing
on heap would be more laborous. */
/* Helps creating a dummy env list with a single element (PWD)
it simply returns a key=value string to add to the node later */
static char	*create_env_helper(t_env *head)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror_exit_free_env("getcwd failed\n", head);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		perror_exit_free_env("Malloc failed\n", head);
	free (cwd);
	return (pwd);
}

static t_env	*create_env(t_env **head)
{
	t_env	*node2;

	(*head)->key_value = create_env_helper(*head);
	(*head)->next = NULL;
	create_user_node(head);
	node2 = malloc (sizeof (t_env));
	if (!node2)
		perror_exit_free_env("Malloc failed\n", *head);
	node2->key_value = ft_strdup("SHLVL=0");
	if (node2->key_value == NULL)
		perror_exit_free_env("Malloc failed\n", *head);
	add_node_to_list(head, node2);
	node2->next = NULL;
	return (*head);
}

/* Counts the amount of envp elements */
static int	get_list_size(char **envp)
{
	int	size;
	int	i;

	if (!envp)
		return (0);
	i = -1;
	size = 0;
	while (envp[++i])
		size++;
	return (size);
}

/* Receives envp, and initializes list creation. Returns 
the head of the created linear linked list */
t_env	*init_env(char **envp)
{
	int		size;
	int		i;
	t_env	*head;

	size = get_list_size(envp);
	head = malloc (sizeof (t_env));
	if (!head)
		perror("Malloc failed\n");
	if (!size)
		return (create_env(&head));
	i = 0;
	head->key_value = ft_strdup(envp[i++]);
	if (head->key_value == NULL)
		perror_exit_free_env("Malloc failed\n", head);
	head->next = NULL;
	while (i < size)
		add_node_to_list(&head, create_node(envp[i++], head));
	if (!find_env_node(head, "USER"))
		create_user_node(&head);
	increase_shell_level(&head);
	return (head);
}

t_env	*create_user_node(t_env **head)
{
	t_env	*node;

	node = ft_calloc (1, sizeof (t_env));
	if (node == NULL)
		perror_exit_free_env("Malloc failed\n", *head);
	node->key_value = ft_strdup("USER=anonymus");
	if (!node->key_value)
		perror_exit_free_env("Malloc failed", *head);
	add_node_to_list(head, node);
	return (node);
}

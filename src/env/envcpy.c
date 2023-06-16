#include "../../inc/minishell.h"

/* It is important to check if envp is NULL before accessing it
in order to avoid segmentation faults and other errors. 
Need cpy of env because maintaining the original through reallocing
on heap would be more laborous. */

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
		perror_exit("Malloc failed\n");
	if (!size)
		return (create_env(head));
	i = 0;
	head->key_value = ft_strdup(envp[i++]);
	if (head->key_value == NULL)
		perror_exit("Malloc failed\n");
	head->next = NULL;
	while (i < size)
		add_node_to_list(head, create_node(envp[i++]));
	if (!find_env_node(head, "USER"))
		create_user_node(head);
	increase_shell_level(head);
	return (head);
}

/* Receives a str as "key=value". If not, it returns NULL.
Creates a single node and sets next pointer to NULL. Returns the node */
t_env	*create_node(char *str)
{
	t_env	*temp;

	if (!str)
		return (NULL);
	temp = malloc (sizeof (t_env));
	if (!temp)
		perror_exit("Malloc failed\n");
	temp->key_value = ft_strdup(str);
	if (temp->key_value == NULL)
		perror_exit("Malloc failed\n");
	temp->key_value = ft_strjoin(temp->key_value, "");
	if (temp->key_value == NULL)
		perror_exit("Malloc failed\n");
	temp->next = NULL;
	return (temp);
}

/* Counts the amount of envp elements */
int	get_list_size(char **envp)
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

/* prints the environment line by line */
void	print_env(t_env *env)
{
	t_env	*node;

	node = env;
	while (node != NULL)
	{
		ft_putendl_fd(node->key_value, STDOUT_FILENO);
		node = node->next;
	}
	g_stat = 0;
}

/* Helps creating a dummy env list with a single element (PWD)
it simply returns a key=value string to add to the node later */
static char	*create_env_helper(void)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror_exit("getcwd failed\n");
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		perror_exit("Malloc failed\n");
	free (cwd);
	return (pwd);
}

t_env	*create_user_node(t_env *head)
{
	t_env	*node;

	node = malloc (sizeof (t_env));
	node->key_value = ft_strdup("USER=anonymus");
	if (!node->key_value)
		perror_exit("Malloc failed\n");
	add_node_to_list(head, node);
	return (node);
}

t_env	*create_env(t_env *head)
{
	t_env	*node2;

	head->key_value = create_env_helper();
	head->next = NULL;
	create_user_node(head);
	node2 = malloc (sizeof (t_env));
	if (!node2)
		perror_exit("Malloc_failed");
	node2->key_value = ft_strdup("SHLVL=0");
	add_node_to_list(head, node2);
	node2->next = NULL;
	return (head);
}

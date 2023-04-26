#include "../inc/minishell.h"

/* It is important to check if envp is NULL before accessing it
in order to avoid segmentation faults and other errors. 

Need cpy of env because maintaining the original through reallocing
on heap would be more laborous. */

t_env	*init_env(char **envp)
{
	int		size;
	int		i;
	t_env	*head;

	size = get_list_size(envp);
	head = malloc (sizeof (t_env *));
	if (!head)
		perror ("Malloc failed");
	i = 0;
	if (!size)
	{
		head->key_value = create_env();
		return (head);
	}
	head->key_value = ft_strdup(envp[i++]);
	if (head->key_value == NULL)
		perror ("Malloc failed");
	head->key_value = ft_strjoin(head->key_value, "");
	if (head->key_value == NULL)
		perror ("Malloc failed");
	head->next = NULL;
	while (i < size)
		ft_lstadd_back_env(&head, create_node(envp[i++]));
	return (head);
}

t_env	*create_node(char *str)
{
	t_env	*temp;

	if (!str)
		return (NULL);
	temp = malloc (sizeof (t_env));
	if (!temp)
		perror ("Malloc failed");
	temp->key_value = ft_strdup(str);
	if (temp->key_value == NULL)
		perror ("Malloc failed");
	temp->key_value = ft_strjoin(temp->key_value, "");
	if (temp->key_value == NULL)
		perror ("Malloc failed");
	temp->next = NULL;
	return (temp);
}

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

void	print_env(t_env *env)
{
	t_env	*node;

	node = env;
	while (node != NULL)
	{
		printf("%s\n", node->key_value);
		node = node->next;
	}
}

char	*create_env(void)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror ("getcwd failed");
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		perror ("Malloc failed");
	free (cwd);
	return (pwd);
}

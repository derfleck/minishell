#include "../../inc/minishell.h"

/* gets the current working directory and prints it on the screen */
int	builtin_pwd(t_env *head)
{
	char	*buf;

	g_stat = 0;
	(void)head; //set_env_command(head);
	buf = getcwd(NULL, 0);
	if (buf)
	{
		printf("%s\n", buf);
		free(buf);
	}
	else
		g_stat = 1;
	return (g_stat);
}

// void	set_env_command(t_env *head)
// {
// 	t_env	*node;

// 	printf("Hello1 \n");
// 	node = find_env_node(head, "_");
// 	printf("Hello2 \n%s", node->key_value);
// 	if (!node)
// 	{
// 		node = create_node("_=usr/bin");
// 		add_node_to_list(head, node);
// 	}
// 	else
// 		replace_node_value(node, "usr/bin");
// }

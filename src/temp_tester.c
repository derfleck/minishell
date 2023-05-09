#include "../inc/minishell.h"

void	env_tester(char *key, t_env **env)
{
	t_env	*node;
	char	*p1;
	char	*p2;

	printf("Testing environment functions. key tested: %s\n", key);
	node = find_env_node(env, key);
	if (node == NULL)
		exit (1);
	printf("Funct: find_env_node returns:   %s\n", node->key_value);
	p1 = split_env_value(node->key_value);
	printf("Funct: split_env_value returns:   %s\n", p1);
	p2 = split_env_key(node->key_value);
	printf("Funct: split_env_key returns:   %s\n", p2);
	printf("Funct: replace_node:  Old keyvalue: %s\n", node->key_value);
	node = replace_node_value(node, "NEW=value_set=yeeees.");
	printf("Funct: replace_node:  New keyvalue: %s\n", node->key_value);
}

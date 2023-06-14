#include "../inc/minishell.h"

int	ft_isnum(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
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

void	increase_shell_level(t_env *env)
{
	t_env	*node;
	char	*new_slvl;

	node = find_env_node(env, "SHLVL");
	if (node)
	{
		new_slvl = ft_itoa(ft_atoi(split_env_value(node->key_value)) + 1);
		replace_node_value(node, new_slvl);
		new_slvl = free_ptr(new_slvl);
	}
	else
		add_node_to_list(env, create_node("SHLVL=1"));
}

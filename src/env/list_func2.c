/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:34:10 by rmocsai           #+#    #+#             */
/*   Updated: 2023/06/29 12:34:58 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Allow only alphanumericals and the '_' in the key received.
If true, it returns 1. If false, it returns 0. 
Also returns 0 if key is only nrs OR starts with digit.
If the last element before the null is +, returns -1 (important for export) */
int	key_validity_check(char *key)
{
	int	i;
	int	len;
	int	nrs;

	i = -1;
	nrs = 0;
	len = ft_strlen(key) - 1;
	if (ft_isnum((int)key[0]))
		return (0);
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			if (i == len && key[i] == '+')
				return (-1);
			else
				return (0);
		}
		if (ft_isnum(key[i]))
			nrs++;
	}
	if (nrs == len + 1)
		return (0);
	else
		return (1);
}

/* Receives a str as "key=value". If not, it returns NULL.
Creates a single node and sets next pointer to NULL. Returns the node 
IMPORTANT: doesn't add created node to list!!! */
t_env	*create_node(char *str, t_env *head)
{
	t_env	*temp;

	if (!str)
		return (NULL);
	temp = malloc(sizeof(t_env));
	if (!temp)
		perror_exit_free_env("Malloc failed\n", head);
	temp->key_value = ft_strdup(str);
	if (temp->key_value == NULL)
		perror_exit_free_env("Malloc failed\n", head);
	temp->next = NULL;
	return (temp);
}

void	increase_shell_level(t_env **env)
{
	t_env	*node;
	char	*new_slvl;

	node = find_env_node(*env, "SHLVL");
	if (node)
	{
		new_slvl = ft_itoa \
		((ft_atoi(split_env_value(node->key_value)) + 1) % 1000);
		if (!new_slvl)
			perror_exit_free_env("Malloc failed \n", *env);
		replace_node_value(node, new_slvl, env);
		new_slvl = free_ptr(new_slvl);
	}
	else
		add_node_to_list(env, create_node("SHLVL=1", *env));
}

/* receives key=value string, splits the value off (everything after
the (=) sign, and returns it as a str.
If something goes wrong, returns a NULL */
char	*split_env_value(char *str)
{
	if (!str)
		return (NULL);
	while (*str != '=' && str)
		str++;
	str++;
	if (!str)
		return (NULL);
	return (str);
}

/* receives key=value string, splits the key off (everything before
the (=) sign, and returns it as an allocated new str
TODO: free key somewhere!!! */
char	*split_env_key(const char *str, t_env *head)
{
	size_t		i;
	char		*key;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	if (!key)
		perror_exit_free_env("Malloc failed\n", head);
	return (key);
}

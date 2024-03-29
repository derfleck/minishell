/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:34:07 by rmocsai           #+#    #+#             */
/*   Updated: 2023/06/29 12:34:59 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* It returns the last element of the env list */
static t_env	*returnlast_env(t_env *lst)
{
	t_env	*lst2;

	if (!lst)
		return ((t_env *)lst);
	lst2 = (t_env *)lst;
	while (lst2->next)
	{
		lst2 = lst2->next;
	}
	return (lst2);
}

/* appends list by adding a node to the end of the list */
void	add_node_to_list(t_env **head, t_env *new)
{
	t_env	*end;

	if (*head)
	{
		if (*head == NULL)
			*head = new;
		else
		{
			end = returnlast_env(*head);
			end->next = new;
		}
	}
}

/* finds and returns env node based on key string received. 
If not found, or no env list, it returns NULL */
t_env	*find_env_node(t_env *head, char *key)
{
	t_env	*node;
	char	*str;
	size_t	len;

	node = head;
	while (node)
	{
		str = split_env_key(node->key_value, head);
		len = ft_strlen(str);
		if (ft_strlen(key) == len && \
			!ft_strncmp(node->key_value, key, ft_strlen(key)))
		{
			free(str);
			return (node);
		}
		free(str);
		node = node->next;
	}
	if (head != NULL && ft_strcmp(key, "USER"))
	{
		node = create_user_node(&head);
		return (node);
	}
	return (NULL);
}

/* Gets env node and char* to replace the current value 
(string after the first '=' sign ). */
void	replace_node_value(t_env *node, char *new_value, t_env **head)
{
	char	*k;
	char	*key;

	if (node == NULL)
		return ;
	k = split_env_key(node->key_value, *head);
	key = ft_strjoin(k, "=");
	if (!k || !key)
		perror_exit_free_env("Malloc failed\n", *head);
	free(k);
	node->key_value = free_ptr(node->key_value);
	node->key_value = ft_strjoin(key, new_value);
	if (node->key_value == NULL)
		perror_exit_free_env("Malloc failed\n", *head);
	free(key);
}

/* Gets env node and str to append it to the existing value in that node. */
void	append_node_value(t_env *node, char *value2, t_env **head)
{
	char	*new_value;

	new_value = ft_strjoin(split_env_value(node->key_value), value2);
	if (!new_value)
		perror_exit_free_env("Malloc failed\n", *head);
	replace_node_value(node, new_value, head);
	free(new_value);
}

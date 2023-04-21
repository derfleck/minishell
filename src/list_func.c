#include "../inc/minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*end;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			end = ft_lstlast_env(*lst);
			end->next = new;
		}
	}
}

t_env	*ft_lstlast_env(t_env *lst)
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
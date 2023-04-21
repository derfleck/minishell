/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:38:08 by mleitner          #+#    #+#             */
/*   Updated: 2023/04/21 18:12:47 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst2;

	if (!lst)
		return ((t_list *)lst);
	lst2 = (t_list *)lst;
	while (lst2->next)
	{
		lst2 = lst2->next;
	}
	return (lst2);
}

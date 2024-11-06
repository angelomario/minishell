/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:29:29 by joandre           #+#    #+#             */
/*   Updated: 2024/05/23 10:29:31 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new;
	t_list	*map;

	if (lst == NULL)
		return (NULL);
	map = NULL;
	temp = lst;
	while (temp != NULL)
	{
		new = ft_lstnew(f(temp->content));
		if (new != NULL)
			ft_lstadd_back(&map, new);
		else
			ft_lstclear(&new, del);
		temp = temp->next;
	}
	return (map);
}

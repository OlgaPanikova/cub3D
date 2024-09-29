/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:32:32 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/31 22:15:29 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
int main()
{
	t_list node1, node2, node3;
	node1.content = "Node 1";
	node1.next = &node2;

	node2.content = "Node 2";
	node2.next = &node3;

	node3.content = "Node 3";
	node3.next = NULL;

	t_list *lastNode = ft_lstlast(&node1);

	if (lastNode)
		printf("Last node content: %s\n", (char *)lastNode->content);
	else
		printf("The list is empty.\n");

	return 0;
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:35:43 by mgreshne          #+#    #+#             */
/*   Updated: 2024/02/01 18:35:43 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	del(void *content)
{
	if (content != NULL)
		free(content);
}*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		(*del)(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

/*int main()
{
	t_list *node1 = malloc(sizeof(t_list));
	node1->content = strdup("Node 1");
	node1->next = malloc(sizeof(t_list));
	node1->next->content = strdup("Node 2");
	node1->next->next = NULL;

	t_list *current = node1;
	while (current)
	{
		printf("Before ft_lstclear: %s\n", (char *)current->content);
		current = current->next;
	}

	ft_lstclear(&node1, del);
	free(node1);

    return 0;
}*/

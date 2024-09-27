/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:36:39 by mgreshne          #+#    #+#             */
/*   Updated: 2024/02/01 18:36:39 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	del(void *content)
{
	if (content != NULL)
		free(content);
}*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

/*int main()
{
	char *str = strdup("Hello, World!");
	t_list *node1 = malloc(sizeof(t_list));
	node1->content = str;
	node1->next = NULL;

	printf("Before ft_lstdelone: %s\n", (char *)node1->content);
	ft_lstdelone(node1, del);
	printf("After ft_lstdelone: (content freed)\n");

	int *num = malloc(sizeof(int));
	*num = 42;
	t_list *node2 = malloc(sizeof(t_list));
	node2->content = num;
	node2->next = NULL;

	printf("Before ft_lstdelone: %d\n", *(int *)node2->content);
	ft_lstdelone(node2, del);
	printf("After ft_lstdelone: (content freed)\n");

	return 0;
}*/

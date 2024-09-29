/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:06:54 by mgreshne          #+#    #+#             */
/*   Updated: 2024/02/01 19:44:30 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	print_content(void *content)
{
	printf("Content: %s\n", (char *)content);
}*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	if (!lst || !f)
		return ;
	ptr = lst;
	while (ptr)
	{
		(*f)(ptr->content);
		ptr = ptr->next;
	}
}

/*int main()
{
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));
	t_list *node3 = malloc(sizeof(t_list));

	node1->content = "Hello";
	node1->next = node2;
	node2->content = "Hello_2";
	node2->next = node3;
	node3->content = "Hello_3";
	node3->next = NULL;
	ft_lstiter(node1, print_content);

	free(node1);
	free(node2);
	free(node3);

	return (0);

}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:10:50 by mgreshne          #+#    #+#             */
/*   Updated: 2024/02/03 17:18:28 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	*format(void *content)
{
	size_t i = 0;
	char *str;
	char *result;

	if (content == NULL)
		return (NULL);
	str = (char *)content;
	result = ft_strdup(str);
	while (result[i])
	{
		result[i] = ft_toupper(result[i]);
		i++;
	}
	return (result);
}

void	del(void *content)
{
	if (content != NULL)
		free(content);
}*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*set;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		set = f(lst->content);
		new_node = ft_lstnew(set);
		if (!new_node)
		{
			del(set);
			ft_lstclear(&new_list, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
int main()
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
	t_list *result = ft_lstmap(node1, format, del);


	free(node1);
	free(node2);
	free(node3);
	ft_lstclear(&result, del);

	return (0);

}*/

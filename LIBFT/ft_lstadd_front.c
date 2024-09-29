/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:15:03 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/31 21:15:21 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int main()
{
	t_list **lst;
	t_list *new;

	lst = (t_list **)malloc(sizeof(t_list *));
	new = ft_lstnew("Hello");
	lst[0]=NULL;
	printf("%s\n",lst[0]);

	lst[0] = new;
	ft_lstadd_front(lst, new);
	printf("%s\n",lst[0]->content);

	// free(new);
}*/

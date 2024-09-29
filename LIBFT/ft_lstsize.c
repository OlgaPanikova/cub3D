/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:18:55 by mgreshne          #+#    #+#             */
/*   Updated: 2024/02/03 17:21:34 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*int main()
{
	t_list *lst = malloc(sizeof(t_list));
	if (!lst)
		return 1;

	lst->content = "hello";
	lst->next = NULL;
	printf("%d\n", ft_lstsize(lst));

	free(lst);
	return 0;
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:07:17 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/25 20:07:17 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*p_new;
	unsigned char	*p_char;
	size_t			total_size;

	total_size = nmemb * size;
	if (nmemb && size && (nmemb > 2147483647 / size))
		return (NULL);
	p_new = (void *)malloc(total_size);
	if (p_new == NULL)
		return (NULL);
	p_char = (unsigned char *)p_new;
	while (total_size > 0)
	{
		*p_char = '\0';
		total_size--;
		p_char++;
	}
	return (p_new);
}

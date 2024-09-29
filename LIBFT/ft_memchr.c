/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:27:30 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/24 19:27:30 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;

	ptr_s = (unsigned char *)s;
	while (n > 0)
	{
		if (*ptr_s == (unsigned char)c)
			return ((void *)ptr_s);
		ptr_s++;
		n--;
	}
	return (NULL);
}

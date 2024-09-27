/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:35:17 by mgreshne          #+#    #+#             */
/*   Updated: 2024/02/02 20:03:13 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	if (!src && !dst)
		return (0);
	ptr_dst = (unsigned char *)dst;
	ptr_src = (const unsigned char *)src;
	while (n-- > 0)
	{
		*ptr_dst = *ptr_src;
		ptr_dst++;
		ptr_src++;
	}
	return (dst);
}

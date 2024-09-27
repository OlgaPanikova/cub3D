/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:54:58 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/22 18:54:58 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;

	if (!dest && !src)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	if (ptr_dest < ptr_src)
	{
		while (len-- > 0)
			*ptr_dest++ = *ptr_src++;
	}
	else
	{
		ptr_dest += len;
		ptr_src += len;
		while (len-- > 0)
			*(--ptr_dest) = *(--ptr_src);
	}
	return (dest);
}

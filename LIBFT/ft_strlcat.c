/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:57:46 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/23 19:57:46 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;
	size_t	remaining_space;

	if (size == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	remaining_space = size - 1 - dst_len;
	i = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] != '\0' && remaining_space > 0)
	{
		dst[dst_len + (i)] = src[i];
		i++;
		remaining_space--;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

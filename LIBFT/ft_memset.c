/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:37:02 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/22 20:41:24 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr_b;

	ptr_b = (unsigned char *)b;
	while (len > 0)
	{
		*ptr_b = (unsigned char)c;
		ptr_b++;
		len--;
	}
	return (b);
}

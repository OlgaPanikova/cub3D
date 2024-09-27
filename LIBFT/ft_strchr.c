/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:21:12 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/28 13:10:40 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	char_c;

	i = 0;
	char_c = (unsigned char)c;
	while (s[i] != '\0' && (unsigned char)s[i] != char_c)
		i++;
	if ((unsigned char)s[i] == char_c)
		return ((char *)&s[i]);
	return (NULL);
}

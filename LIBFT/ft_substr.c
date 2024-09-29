/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:37:55 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/26 19:37:55 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			len_str;

	i = 0;
	str = NULL;
	if (!s)
		return (NULL);
	len_str = ft_strlen(s);
	if (start > len_str)
		start = (unsigned int)len_str;
	if (len > len_str - start)
		len = len_str - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (len-- > 0 && s[start + i] != '\0')
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

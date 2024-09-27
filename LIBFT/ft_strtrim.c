/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:14:45 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/28 13:14:45 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*ptr;

	ptr = dest;
	while (*src && n > 0)
	{
		*dest++ = *src++;
		n--;
	}
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	size_t	len_trimmed;
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]) != NULL)
		end--;
	len_trimmed = end - start + 1;
	trimmed_str = (char *)malloc(sizeof(char) * (len_trimmed + 1));
	if (trimmed_str == NULL)
		return (NULL);
	ft_strncpy(trimmed_str, s1 + start, len_trimmed);
	trimmed_str[len_trimmed] = '\0';
	return (trimmed_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:40:46 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/26 19:40:46 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*container;
	size_t	len_s1s2;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	container = 0;
	len_s1s2 = ft_strlen(s1) + ft_strlen(s2);
	container = (char *)malloc((len_s1s2 + 1) * sizeof(char));
	if (container == NULL)
		return (NULL);
	while (s1[i] != '\0')
		container[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		container[i++] = s2[j++];
	container[i] = '\0';
	return (container);
}

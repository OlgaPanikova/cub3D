/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:17:32 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/30 19:17:32 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static void	ft_plus_32(unsigned int index, char *c)
{
	*c += index;
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s && f)
	{
		while (s[i] != '\0')
		{
			f(i, &(s[i]));
			i++;
		}
	}
}
/*
int main()
{
	char str[] = "abcdf";
	ft_striteri(str, ft_plus_32);

	printf("%s\n", str);
	return 0;
}*/

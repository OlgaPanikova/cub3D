/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:52 by mgreshne          #+#    #+#             */
/*   Updated: 2024/01/31 17:55:59 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		c = n % 10 + '0';
		n = n / 10;
		ft_putnbr_fd(n, fd);
	}
	else
		c = n % 10 + '0';
	write(fd, &c, 1);
}
/*
int main()
{
	int nbr = INT_MIN;
	ft_putnbr_fd(nbr, 1);
	return (0);
}*/

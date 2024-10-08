/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:05:57 by mgreshne          #+#    #+#             */
/*   Updated: 2024/10/08 18:58:29 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_arguments(int args, char **argv, t_cub *data)
{
	if (args != 2)
	{
		free(data);
		return (ft_print_error("Error arguments\n", 1));
	}
	if (!check_file_extension(argv[1]))
	{
		free(data);
		return (ft_print_error("Error\nFile must have a .cub extension\n", 1));
	}
	return (0);
}

int	open_file(t_cub *data, const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_exit(data, "Error\nFile (map) does not open", 1);
	return (fd);
}

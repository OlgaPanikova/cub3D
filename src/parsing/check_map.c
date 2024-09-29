/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:37:09 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/28 22:23:30 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_player(t_cub *data, int i, size_t j, int *player_found)
{
	if (*player_found)
		return (ft_print_error("Error: Multiple player positions in map\n", 1));
	data->posX = j + 0.5;
	data->posY = i + 0.5;
	data->direction = data->map[i][j];
	*player_found = 1;
	return (0);
}

int	check_positions(char pos, char player)
{
	if (pos != '1' && pos != '0' && pos != player)
		return (ft_print_error(("Map should be enclosed with walls\n"), 1));
	return (0);
}

int	check_walls(t_cub *data, int y, int x)
{
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == data->direction)
				data->map[y][x] = '0';
			if (data->map[y][x] == '0')
			{
				if (y == 0 || y == data->map_height)
					return (ft_print_error(("Map should be enclosed with walls\n"), 1));
				if (check_positions(data->map[y - 1][x], data->direction) != 0)
					return (1);
				if (check_positions(data->map[y + 1][x], data->direction) != 0)
					return (1);
				if (check_positions(data->map[y][x - 1], data->direction) != 0)
					return (1);
				if (check_positions(data->map[y][x + 1], data->direction) != 0)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_map(t_cub *data)
{
	int		i;
	int player_found;
	size_t	j;
	size_t len;

	i = 0;
	player_found = 0;
	while (i < data->map_height)
	{
		j = 0;
		len = ft_strlen(data->map[i]);
		while (j < len)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W' || data->map[i][j] == 'E' || data->map[i][j] == 'S')
			{
				if (validate_player(data, i, j, &player_found))
					return (1);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		return (ft_print_error("Error: No player position in map\n", 1));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:37:09 by mgreshne          #+#    #+#             */
/*   Updated: 2024/10/04 13:46:36 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	validate_player(t_cub *data, int i, size_t j, int *player_found)
{
	if (*player_found)
		ft_exit(data, "Error\nMultiple player positions in map", 1);
	data->player.pos_y = j + 0.5;
	data->player.pos_x = i + 0.5;
	data->direction = data->map[i][j];
	*player_found = 1;
}

void	check_positions(t_cub *data, char pos, char player)
{
	if (pos != '1' && pos != '0' && pos != player)
		ft_exit(data, "Error\nMap should be enclosed with walls", 1);
}

void	check_walls(t_cub *data, int y, int x)
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
				if (y == 0 || y == data->map_height - 1)
					ft_exit(data,
						"Error\nMap should be enclosed with walls", 1);
				check_positions(data, data->map[y - 1][x], data->direction);
				check_positions(data, data->map[y + 1][x], data->direction);
				check_positions(data, data->map[y][x - 1], data->direction);
				check_positions(data, data->map[y][x + 1], data->direction);
			}
			x++;
		}
		y++;
	}
}

void	check_map(t_cub *data)
{
	int		i;
	int		player_found;
	size_t	j;
	size_t	len;

	i = 0;
	player_found = 0;
	while (i < data->map_height)
	{
		j = 0;
		len = ft_strlen(data->map[i]);
		while (j < len)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'S')
			{
				validate_player(data, i, j, &player_found);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		ft_exit(data, "Error\nNo player position in map", 1);
}

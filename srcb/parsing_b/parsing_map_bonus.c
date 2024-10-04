/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:36:26 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/29 17:58:47 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**add_line_to_map(char **map, int current_size, char *new_line)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (current_size + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < current_size)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = strdup_until_newline(new_line);
	if (!new_map[i])
	{
		free(new_map);
		return (NULL);
	}
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}

int	is_map_line_valid(const char *line)
{
	while (*line != '\0' && *line != '\n')
	{
		if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}

int	parse_map(t_cub *data, char *line)
{
	data->map = add_line_to_map(data->map, data->map_height, line);
	if (!data->map)
		ft_exit(data, "Error\nmemory not allocated", -1);
	data->map_height++;
	return (0);
}

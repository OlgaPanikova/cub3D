/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:18:05 by mgreshne          #+#    #+#             */
/*   Updated: 2024/10/07 21:41:12 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_color_line(t_cub *data, char *line)
{
	line = skip_spaces(line);
	if (line[0] == 'F')
	{
		if (data->floor_color[0] != -1)
			ft_exit(data, "Error\nDuplicate floor color", 1);
		line++;
		if (parse_color(data, data->floor_color, line) != 0)
			return (ft_print_error("Invalid floor color\n", 1));
		return (0);
	}
	else if (line[0] == 'C')
	{
		if (data->ceiling_color[0] != -1)
			ft_exit(data, "Error\nDuplicate ceiling color", 1);
		line++;
		if (parse_color(data, data->ceiling_color, line) != 0)
			return (ft_print_error("Invalid ceiling color\n", 1));
		return (0);
	}
	return (1);
}

void	handle_texture(t_cub *data, char **texture, char *line,
		const char *identifier)
{
	if (*texture)
		ft_exit(data, "Error\nDuplicate texture", 1);
	parse_texture(data, texture, line, identifier);
}

int	parse_texture_line(t_cub *data, char *line)
{
	line = skip_spaces(line);
	if (ft_strncmp(line, "NO", 2) == 0)
		handle_texture(data, &data->north_texture, line, "NO");
	else if (ft_strncmp(line, "SO", 2) == 0)
		handle_texture(data, &data->south_texture, line, "SO");
	else if (ft_strncmp(line, "WE", 2) == 0)
		handle_texture(data, &data->west_texture, line, "WE");
	else if (ft_strncmp(line, "EA", 2) == 0)
		handle_texture(data, &data->east_texture, line, "EA");
	else
		return (-1);
	return (0);
}

int	process_line(t_cub *data, char *line, int *is_map_parsing,
	int *elements_completed)
{
	if (*is_map_parsing)
	{
		if (!is_map_line_valid(line))
			return (ft_print_error("Error: Invalid map character\n", 1));
		parse_map(data, line);
		return (0);
	}
	if (parse_texture_line(data, line) == 0)
		return (0);
	else if (parse_color_line(data, line) == 0)
		return (0);
	if (check_elements_completed(data))
		*elements_completed = 1;
	if (strchr(line, '1') || strchr(line, '0') || strchr(line, 'N')
		|| strchr(line, 'S') || strchr(line, 'E') || strchr(line, 'W'))
	{
		if (!*elements_completed)
			ft_exit(data, "Error\nThe map was announced before all data", 1);
		*is_map_parsing = 1;
		return (process_line(data, line, is_map_parsing, elements_completed));
	}
	if (!is_map_line_valid(line))
		ft_exit(data,
			"Error\nIndependent lines contain unnecessary information", 1);
	return (0);
}

int	parsing_args(t_cub *data, const char *file)
{
	int		fd;

	fd = open_file(data, file);
	if (parse_lines(data, fd) != 0)
	{
		close(fd);
		return (1);
	}
	check_after_map(fd, data);
	close(fd);
	if (check_texture_files(data) != 0)
		return (1);
	if (data->map)
		check_map(data);
	else
		ft_exit(data, "Error\ngame map is missing", 1);
	check_walls(data, 0, 0);
	return (0);
}

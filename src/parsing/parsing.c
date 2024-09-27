/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:18:05 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/23 21:18:05 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_extension(const char *filename)
{
	const char	*ext;
	size_t		len_filename;
	size_t		len_ext;

	ext = ".cub";
	len_filename = strlen(filename);
	len_ext = strlen(ext);

	if (len_filename <= len_ext)
		return (0);

	return (strncmp(filename + len_filename - len_ext, ext, len_ext) == 0);
}

int	parse_color_line(t_cub *data, char *line)
{
	printf("tyt парсинг колор?\n");
	line = skip_spaces(line);
	if (line[0] == 'F')
	{
		line++;
		if (parse_color(data->floor_color, line) != 0)
			return (ft_print_error("Invalid floor color\n", 1));
		printf("tyt парсинг колор заполнил\n");
		return (0);
	}
	else if (line[0] == 'C')
	{
		line++;
		if (parse_color(data->ceiling_color, line) != 0)
			return (ft_print_error("Invalid ceiling color\n", 1));
		printf("tyt парсинг колор заполнил\n");
		return (0);
	}
	printf("tyt парсинг колор ничего не заполнил\n");
	return (1);
}

int	parse_texture_line(t_cub *data, char *line)
{
	printf("tyt парсинг текстуры\n");
	line = skip_spaces(line);
	if (strncmp(line, "NO", 2) == 0)
		return (parse_texture(&data->north_texture, line, "NO"));
	else if (strncmp(line, "SO", 2) == 0)
		return (parse_texture(&data->south_texture, line, "SO"));
	else if (strncmp(line, "WE", 2) == 0)
		return (parse_texture(&data->west_texture, line, "WE"));
	else if (strncmp(line, "EA", 2) == 0)
		return (parse_texture(&data->east_texture, line, "EA"));
	printf("tyt парсинг текстуры ничего не заполнил\n");
	return (-1);
}

int	check_elements_completed(t_cub *data)
{
	if (data->north_texture && data->south_texture && data->west_texture &&
		data->east_texture && data->floor_color[0] != -1 && data->ceiling_color[0] != -1)
		return (1);
	return (0);
}

int	process_line(t_cub *data, char *line, int *is_map_parsing, int *elements_completed)
{
	printf("tyt ппроверка карта есть?\n");
	if (*is_map_parsing)
	{
		if (!is_map_line_valid(line))
		{
			free_data(data);
			return (ft_print_error("Error: Invalid map character\n", 1));
		}
		if (parse_map(data, line) != 0)
		{
			free_data(data);
			return (ft_print_error("Error: Failed to parse map\n", 1));
		}
		return (0);
	}
	printf("tyt парсинг текстуры или колор?\n");
	if (parse_texture_line(data, line) == 0)
		return (0);
	else if (parse_color_line(data, line) == 0)
		return (0);
	printf("tyt начинается просмотр карты\n");
	if (check_elements_completed(data))
		*elements_completed = 1;
	if (strchr(line, '1') || strchr(line, '0') || strchr(line, 'N')
		|| strchr(line, 'S') || strchr(line, 'E') || strchr(line, 'W'))
	{
		if (!*elements_completed)
			return (ft_print_error("Error: Map found before completing textures and colors\n", 1));
		*is_map_parsing = 1;
		printf("tyt будет заполняться карта вероятнее\n");
		return (process_line(data, line, is_map_parsing, elements_completed));
	}
	return (0);
}


int	parsing_args(t_cub *data, const char *file)
{
	int		fd;
	char	*line;
	int		is_map_parsing = 0;
	int		elements_completed = 0;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_print_error("Error opening file\n", 1));
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_parsing && (*line == '\0' || *line == '\n' || skip_spaces(line)[0] == '\0'))
			break;
		if (process_line(data, line, &is_map_parsing, &elements_completed) != 0)
		{
			free(line);
			close(fd);
			free_data(data);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		if (*line == '\0' || *line == '\n' || skip_spaces(line)[0] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		close(fd);
		return (ft_print_error("Error\nThere should be nothing after the map\n", 1));
	}

	if (check_texture_files(data) != 0)
	{
		close(fd);
		return (1);
	}

	/*
	if (check_map_borders(data) != 0 || check_player_position(data) != 0)
	{
		free_data(data);
		close(fd);
		return (1);
	}
	*/

	close(fd);
	return (0);
}

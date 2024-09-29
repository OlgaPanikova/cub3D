/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:36:33 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/29 17:37:51 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*parse_single_color(t_cub *data, char *line)
{
	char	*end;

	if (!ft_isdigit(*line))
		ft_exit(data,
			"Error\nNon-digit character encountered in color value", 1);
	end = line;
	while (*end && ft_isdigit(*end))
		end++;
	return (end);
}


int	check_texture_extension(const char *filename)
{
	const char	*ext;
	size_t		len_filename;
	size_t		len_ext;

	ext = ".xpm";
	len_filename = ft_strlen(filename);
	len_ext = ft_strlen(ext);
	if (len_filename <= len_ext)
		return (0);
	return (ft_strncmp(filename + len_filename - len_ext, ext, len_ext) == 0);
}

int	check_texture_file(const char *filename)
{
	int	fd;

	if (!check_texture_extension(filename))
		return (ft_print_error("Error: Invalid texture file format (must be .xpm)\n", 1));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_print_error("Error: Texture file not found\n", 1));
	close(fd);
	return (0);
}

int	check_texture_files(t_cub *data)
{
	if (check_texture_file(data->north_texture) != 0)
		return (1);
	if (check_texture_file(data->south_texture) != 0)
		return (1);
	if (check_texture_file(data->west_texture) != 0)
		return (1);
	if (check_texture_file(data->east_texture) != 0)
		return (1);
	return (0);
}


char	*skip_spaces(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

int	parse_color(t_cub *data, int *color, char *line)
{
	int		i;
	char	*end;

	line = skip_spaces(line);
	i = 0;
	while (i < 3)
	{
		end = parse_single_color(data, line);
		color[i] = ft_atoi(line);
		if (color[i] < 0 || color[i] > 255)
			ft_exit(data, "Error\nColor value out of range (0-255)", 1);
		line = end;
		line = skip_spaces(line);
		if (i < 2)
		{
			if (*line != ',')
				ft_exit(data, "Error\nMissing comma between color values", 1);
			line++;
		}
		line = skip_spaces(line);
		i++;
	}
	return (0);
}

int	parse_texture(t_cub *data, char **dest, char *line, const char *identifier)
{
		line += ft_strlen(identifier);
		line = skip_spaces(line);
		*dest = strdup_until_newline(line);;
		if (!*dest)
			ft_exit(data, "Error\nmemory not allocated", -1);
		return (0);
}

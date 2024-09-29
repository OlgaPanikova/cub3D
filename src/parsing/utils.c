/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:18:05 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/29 18:03:55 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*skip_spaces(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
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

int	check_file_extension(const char *filename)
{
	const char	*ext;
	size_t		len_filename;
	size_t		len_ext;

	ext = ".cub";
	len_filename = ft_strlen(filename);
	len_ext = ft_strlen(ext);

	if (len_filename <= len_ext)
		return (0);
	return (ft_strncmp(filename + len_filename - len_ext, ext, len_ext) == 0);
}

void	rgb_to_hex(t_cub *data)
{
	data->hex_floor = (data->floor_color[0] << 16)
		| (data->floor_color[1] << 8) | data->floor_color[2];
	data->hex_ceiling = (data->ceiling_color[0] << 16)
		| (data->ceiling_color[1] << 8) | data->ceiling_color[2];
}

char	*strdup_until_newline(const char *line)
{
	int		len;
	char	*new_str;
	int		i;

	len = 0;
	while (line[len] != '\n' && line[len] != '\0')
		len++;

	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = line[i];
		i++;
	}
	new_str[len] = '\0';
	return (new_str);
}

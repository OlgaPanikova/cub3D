/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:18:05 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/23 21:18:05 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rgb_to_hex(t_cub *data)
{
	data->hex_floor = (data->floor_color[0] << 16) | (data->floor_color[1] << 8) | data->floor_color[2];
	data->hex_ceiling = (data->ceiling_color[0] << 16) | (data->ceiling_color[1] << 8) | data->ceiling_color[2];
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
		return NULL; // или что то другое? выходить из программы?
	i = 0;
	while (i < len)
	{
		new_str[i] = line[i];
		i++;
	}
	new_str[len] = '\0';
	return (new_str);
}

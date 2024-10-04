/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:41:36 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 12:59:30 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ceiling(t_cub *data)
{
	int	half_height;
	int	y;
	int	x;

	half_height = data->hight_screen / 2;
	y = 0;
	while (y < half_height)
	{
		x = 0;
		while (x < data->wight_screen)
		{
			data->image->addr[y * data->wight_screen + x++] = data->hex_ceiling;
		}
		y++;
	}
}

void	draw_floor(t_cub *data)
{
	unsigned int	*pixels;
	int				half_height;
	int				i;
	int				j;

	pixels = (unsigned int *)data->image->addr;
	half_height = data->hight_screen / 2;
	i = half_height;
	while (i < data->hight_screen)
	{
		j = 0;
		while (j < data->wight_screen)
		{
			pixels[i * data->wight_screen + j] = data->hex_floor;
			j++;
		}
		i++;
	}
}

void	draw_floor_and_ceiling(t_cub *data)
{
	draw_ceiling(data);
	draw_floor(data);
}

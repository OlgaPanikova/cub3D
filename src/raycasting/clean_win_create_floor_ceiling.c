/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_win_create_floor_ceiling.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:41:36 by opanikov          #+#    #+#             */
/*   Updated: 2024/09/29 16:06:31 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_ceiling(t_cub *data)
{
	unsigned int	*pixels;
	int				half_height;
	int				y;
	int				x;

	pixels = (unsigned int *)data->img_data;
	half_height = data->h / 2;
	y = 0;
	while (y < half_height)
	{
		x = 0;
		while (x < data->w)
		{
			pixels[y * data->w + x] = data->hex_ceiling;
			x++;
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

	pixels = (unsigned int *)data->img_data;
	half_height = data->h / 2;
	i = half_height;
	while (i < data->h)
	{
		j = 0;
		while (j < data->w)
		{
			pixels[i * data->w + j] = data->hex_floor;
			j++;
		}
		i++;
	}
}
void	draw_floor_and_ceiling(t_cub *data)
{
	draw_ceiling(data);  // Отрисовка потолка
	draw_floor(data);      // Отрисовка пола
}

void	clear_image(t_cub *data)
{
	unsigned int	*pixels;
	int				num_pixels;
	int				i;

	i = 0;
	data->img = mlx_new_image(data->mlx_ptr, data->w, data->h);
	data->img_data = (int *)mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);

	pixels = (unsigned int *)data->img_data;
	num_pixels = data->w * data->h;
	while (i < num_pixels)
	{
		pixels[i] = 0x000000; // Черный цвет
		i++;
	}
}
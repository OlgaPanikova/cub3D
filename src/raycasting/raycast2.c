/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:58:09 by opanikov          #+#    #+#             */
/*   Updated: 2024/09/29 15:14:04 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_wall(t_cub *data, int x, int drawStart, int drawEnd, double wallX, int *texture_data, int lineHeight)
{
	int texX;
	double step;
	double texPos;

	// Выбор текстуры и расчет texX
	texture_data = select_texture(data, wallX, &texX);

	// Расчет шага по текстуре и начальной позиции
	step = calculate_texture_step(lineHeight);
	texPos = calculate_initial_texture_position(drawStart, lineHeight, data->h);

	// Отрисовка стены
	render_wall_slice(data, x, drawStart, drawEnd, texX, texPos, step, texture_data);
}


double	calculate_wall_hit_position(t_cub *data, double perpWallDist)
{
	double wallX;

	if (data->ray.side == 0)
		wallX = data->player.posY + perpWallDist * data->ray.rayDirY;
	else
		wallX = data->player.posX + perpWallDist * data->ray.rayDirX;

	wallX -= (int)wallX;  // Получаем дробную часть
	return wallX;
}

void	calculate_wall_dimensions(t_cub *data, double perpWallDist, int *lineHeight, int *drawStart, int *drawEnd)
{
	*lineHeight = (int)(data->h / perpWallDist);
	*drawStart = -(*lineHeight) / 2 + data->h / 2;
	*drawEnd = *lineHeight / 2 + data->h / 2;

	if (*drawStart < 0)
		*drawStart = 0;
	if (*drawEnd >= data->h)
		*drawEnd = data->h - 1;
}

void	render_wall(t_cub *data, int x)
{
	double perpWallDist;
	int lineHeight;
	int drawStart;
	int drawEnd;
	double wallX;
	int *texture_data;

	// Расчет направления и столкновений
	calculate_ray_direction(data, x);
	calculate_initial_step(data);
	detect_wall_hit(data);

	// Расчет расстояния до стены
	perpWallDist = calculate_perpendicular_distance(data);

	// Расчет высоты стены и границ
	calculate_wall_dimensions(data, perpWallDist, &lineHeight, &drawStart, &drawEnd);

	// Расчет позиции удара луча по стене
	wallX = calculate_wall_hit_position(data, perpWallDist);

	// Получение текстурных данных
	texture_data = (int *)mlx_get_data_addr(data->textures[0], &data->bpp, &data->size_line, &data->endian);

	// Отрисовка стены
	draw_wall(data, x, drawStart, drawEnd, wallX, texture_data, lineHeight);
}

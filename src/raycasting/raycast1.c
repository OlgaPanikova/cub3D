/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:40:51 by opanikov          #+#    #+#             */
/*   Updated: 2024/09/29 17:16:58 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	calculate_perpendicular_distance(t_cub *data)
{
	if (data->ray.side == 0)
	{
		return (data->ray.mapX - data->player.posX + (1 - data->ray.stepX) / 2) / data->ray.rayDirX;
	}
	else
	{
		return (data->ray.mapY - data->player.posY + (1 - data->ray.stepY) / 2) / data->ray.rayDirY;
	}
}

int	detect_wall_hit(t_cub *data)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray.sideDistX < data->ray.sideDistY)
		{
			data->ray.sideDistX += data->ray.deltaDistX;
			data->ray.mapX += data->ray.stepX;
			data->ray.side = 0;
		}
		else
		{
			data->ray.sideDistY += data->ray.deltaDistY;
			data->ray.mapY += data->ray.stepY;
			data->ray.side = 1;
		}
		if (data->map[data->ray.mapX][data->ray.mapY] > '0')
			hit = 1;
		// printf("Map value at [4][2]: %d\n", data->map[4][2]);
		// printf("Checking mapX = %d, mapY = %d\n", data->ray.mapX, data->ray.mapY);
	}
	return (hit);
}

double	absValue(double x)
{
	if (x < 0)
		return -x;
	else
		return x;
}

void	calculate_ray_direction(t_cub *data, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)data->w - 1;
	data->ray.rayDirX = data->player.dirX + data->player.planeX * cameraX;
	data->ray.rayDirY = data->player.dirY + data->player.planeY * cameraX;
	data->ray.mapX = (int)data->player.posX;
	data->ray.mapY = (int)data->player.posY;
	data->ray.deltaDistY = absValue(1 / data->ray.rayDirY);
	data->ray.deltaDistX = absValue(1 / data->ray.rayDirX);
}

void calculate_initial_step(t_cub *data)
{
	if (data->ray.rayDirX < 0)
	{
		data->ray.stepX = -1;
		data->ray.sideDistX = (data->player.posX - data->ray.mapX) * data->ray.deltaDistX;
	}
	else
	{
		data->ray.stepX = 1;
		data->ray.sideDistX = (data->ray.mapX + 1.0 - data->player.posX) * data->ray.deltaDistX;
	}
	if (data->ray.rayDirY < 0)
	{
		data->ray.stepY = -1;
		data->ray.sideDistY = (data->player.posY - data->ray.mapY) * data->ray.deltaDistY;
	}
	else
	{
		data->ray.stepY = 1;
		data->ray.sideDistY = (data->ray.mapY + 1.0 - data->player.posY) * data->ray.deltaDistY;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:40:51 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/03 17:48:40 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_wall(t_cub *data, int x)
{
	int	y;

	data->texx = (int)(data->ray.wallx * (double)data->wallt->width);
	if ((data->ray.side == 0 && data->ray.rayDirX > 0) \
		|| (data->ray.side == 1 && data->ray.rayDirY < 0))
		data->texx = data->wallt->width - data->texx - 1;
	data->texheight = (int)(data->hight_screen / data->ray.perpWallDist);
	data->drawstart = -data->texheight / 2 + data->hight_screen / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->texheight / 2 + data->hight_screen / 2;
	if (data->drawend >= data->hight_screen)
		data->drawend = data->hight_screen - 1;
	y = data->drawstart;
	while (y < data->drawend)
	{
		data->texy = (int)(((y - data->hight_screen / 2 + data->texheight / 2) \
			* data->wallt->height) / data->texheight);
		data->color = data->wallt->addr[data->texy \
			* data->wallt->width + data->texx];
		data->image->addr[y * data->wight_screen + x] = data->color;
		y++;
	}
}

void	side_of_the_wall(t_cub *data)
{
	if (data->ray.side == 0)
	{
		if (data->ray.rayDirX > 0)
			data->wallt = data->e;
		else
			data->wallt = data->w;
	}
	else
	{
		if (data->ray.rayDirY > 0)
			data->wallt = data->n;
		else
			data->wallt = data->s;
	}
}

void	calculate_wall_rendering(t_cub *data)
{
	if (data->ray.side == 0)
		data->ray.perpWallDist = (data->ray.sideDistX - data->ray.deltaDistX);
	else
		data->ray.perpWallDist = (data->ray.sideDistY - data->ray.deltaDistY);
	data->lineheight = (int)(data->hight_screen / data->ray.perpWallDist);
	data->drawstart = -data->lineheight / 2 + data->hight_screen / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineheight / 2 + data->hight_screen / 2;
	if (data->drawend >= data->hight_screen)
		data->drawend = data->hight_screen - 1;
	if (data->ray.side == 1)
		data->color = data->color / 2;
	if (data->ray.side == 0)
		data->ray.wallx = data->player.posY + data->ray.perpWallDist * data->ray.rayDirY;
	else
		data->ray.wallx = data->player.posX + data->ray.perpWallDist * data->ray.rayDirX;
	data->ray.wallx -= floor(data->ray.wallx);
}

void	detect_wall_hit(t_cub *data)
{

	while (data->ray.hit == 0)
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
		if (data->map[data->ray.mapX][data->ray.mapY] == '1')
			data->ray.hit = 1;
	}
}

void	calculate_initial_step(t_cub *data)
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

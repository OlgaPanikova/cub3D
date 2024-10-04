/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:40:51 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 14:20:03 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_wall(t_cub *data, int x)
{
	int	y;

	data->texx = (int)(data->ray.wallx * (double)data->wallt->width);
	if ((data->ray.side == 0 && data->ray.ray_dir_x > 0) \
		|| (data->ray.side == 1 && data->ray.ray_dir_y < 0))
		data->texx = data->wallt->width - data->texx - 1;
	data->texheight = (int)(data->hight_screen / data->ray.perp_wall_dist);
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
		if (data->ray.ray_dir_x > 0)
			data->wallt = data->e;
		else
			data->wallt = data->w;
	}
	else
	{
		if (data->ray.ray_dir_y > 0)
			data->wallt = data->n;
		else
			data->wallt = data->s;
	}
}

void	calculate_wall_rendering(t_cub *data)
{
	if (data->ray.side == 0)
		data->ray.perp_wall_dist = (data->ray.side_dist_x - data->ray.delta_dist_x);
	else
		data->ray.perp_wall_dist = (data->ray.side_dist_y - data->ray.delta_dist_y);
	data->lineheight = (int)(data->hight_screen / data->ray.perp_wall_dist);
	data->drawstart = -data->lineheight / 2 + data->hight_screen / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineheight / 2 + data->hight_screen / 2;
	if (data->drawend >= data->hight_screen)
		data->drawend = data->hight_screen - 1;
	if (data->ray.side == 1)
		data->color = data->color / 2;
	if (data->ray.side == 0)
		data->ray.wallx = data->player.pos_y + data->ray.perp_wall_dist
			* data->ray.ray_dir_y;
	else
		data->ray.wallx = data->player.pos_x + data->ray.perp_wall_dist
			* data->ray.ray_dir_x;
	data->ray.wallx -= floor(data->ray.wallx);
}

void	detect_wall_hit(t_cub *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map[data->ray.map_x][data->ray.map_y] == '1')
			data->ray.hit = 1;
	}
}

void	calculate_initial_step(t_cub *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.pos_x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.pos_x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.pos_y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.pos_y)
			* data->ray.delta_dist_y;
	}
}

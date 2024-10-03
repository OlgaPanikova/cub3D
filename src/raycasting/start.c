/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:26:26 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/03 20:11:51 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_ray_direction(t_cub *data, int x)
{
	data->ray.cameraX = 2 * x / (double)data->wight_screen - 1;
	data->ray.rayDirX = data->player.dirX + data->player.planeX * data->ray.cameraX;
	data->ray.rayDirY = data->player.dirY + data->player.planeY * data->ray.cameraX;
	data->ray.mapX = (int)data->player.posX;
	data->ray.mapY = (int)data->player.posY;
	if (data->ray.rayDirX == 0)
		data->ray.deltaDistX = 1e30;
	else
		data->ray.deltaDistX = fabs(1 / data->ray.rayDirX);
	if (data->ray.rayDirY == 0)
		data->ray.deltaDistY = 1e30;
	else
		data->ray.deltaDistY = fabs(1 / data->ray.rayDirY);
	data->ray.hit = 0;
}

void	render(t_cub *data)
{
	int	x;

	x = 0;
	while (x < data->wight_screen)
	{
		calculate_ray_direction(data, x);
		calculate_initial_step(data);
		detect_wall_hit(data);
		calculate_wall_rendering(data);
		side_of_the_wall(data);
		draw_wall(data, x);
		x++;
	}
}

void	start_raycast(t_cub *data)
{
	data->image = malloc(sizeof(t_texture));
	data->image->img = mlx_new_image(data->mlx_ptr, data->wight_screen, data->hight_screen);
	data->image->addr = (int *)mlx_get_data_addr(data->image->img, &data->image->bpp, &data->image->size_line, &data->image->endian);
	draw_floor_and_ceiling(data);
	render(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->image->img);
	free(data->image);
}

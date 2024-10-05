/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:26:26 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/05 15:36:50 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_move(int x, int y, t_cub *data)
{
	mlx_mouse_hide();
	mlx_mouse_get_pos(data->win_ptr, &x, &y);
	if (x > data->wight_screen / 2)
		key_hook(124, data);
	if (x < data->wight_screen / 2)
		key_hook(123, data);
	mlx_mouse_move(data->win_ptr, data->wight_screen / 2, y / 2);
	return (0);
}

void	calculate_ray_direction(t_cub *data, int x)
{
	data->ray.camera_x = 2 * x / (double)data->wight_screen - 1;
	data->ray.ray_dir_x = data->player.dir_x + data->player.plane_x
		* data->ray.camera_x;
	data->ray.ray_dir_y = data->player.dir_y + data->player.plane_y
		* data->ray.camera_x;
	data->ray.map_x = (int)data->player.pos_x;
	data->ray.map_y = (int)data->player.pos_y;
	if (data->ray.ray_dir_x == 0)
		data->ray.delta_dist_x = 1e30;
	else
		data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	if (data->ray.ray_dir_y == 0)
		data->ray.delta_dist_y = 1e30;
	else
		data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
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
	data->image->img = mlx_new_image(data->mlx_ptr, data->wight_screen,
			data->hight_screen);
	data->image->addr = (int *)mlx_get_data_addr(data->image->img,
			&data->image->bpp, &data->image->size_line, &data->image->endian);
	draw_floor_and_ceiling(data);
	render(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->image->img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->image->img);
	free(data->image);
	update_player_animation(data);
	render_player(data);
}

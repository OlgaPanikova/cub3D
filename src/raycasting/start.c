/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:26:26 by opanikov          #+#    #+#             */
/*   Updated: 2024/09/29 17:03:11 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculations_camera(t_cub *data, char direction)
{
	if (direction == 'N')
	{
		data->player.dirX = 0;
		data->player.dirY = -1;
		data->player.planeX = 0.66;
		data->player.planeY = 0;
	}
	else if (direction == 'S') // Смотрит на юг
	{
		data->player.dirX = 0;
		data->player.dirY = 1;
		data->player.planeX = -0.66;
		data->player.planeY = 0;
	}
	else if (direction == 'W') // Смотрит на запад
	{
		data->player.dirX = -1;
		data->player.dirY = 0;
		data->player.planeX = 0;
		data->player.planeY = 0.66;
	}
	else if (direction == 'E') // Смотрит на восток
	{
		data->player.dirX = 1;
		data->player.dirY = 0;
		data->player.planeX = 0;
		data->player.planeY = -0.66;
	}
}

void	process_input(t_cub *data)
{
	if (data->keys->up)
		move_forward(data);
	if (data->keys->down)
		move_backward(data);
	if (data->keys->left)
		move_left(data);
	if (data->keys->right)
		move_right(data);
	if (data->keys->pov_left)
		rotate_left(data);
	if (data->keys->pov_right)
		rotate_right(data);
}

int render(void *param)
{
	t_cub *data = (t_cub *)param;
	int	x;

	clear_image(data);
	draw_floor_and_ceiling(data);
	x = 0;
	while (x < data->w)
	{
		render_wall(data, x);
		x++;
	}
	process_input(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img);
	return (0);
}

void	start_raycast(t_cub *data)
{
	init_texture(data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_hook, data->keys);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_release_hook, data->keys);
    // mlx_hook(win_ptr, 6, 0, mouse_move, data);
	mlx_hook(data->win_ptr, 17, 0L, close_window, data); // добавить очистку памяти 
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_loop(data->mlx_ptr);
}


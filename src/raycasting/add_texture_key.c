/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:47:39 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/03 17:41:38 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculations_camera(t_cub *data, char direction)
{
	if (direction == 'N')
	{
		data->player.dirY = 0;
		data->player.dirX = -1;
		data->player.planeY = 0.66;
		data->player.planeX = 0;
	}
	else if (direction == 'S') // Смотрит на юг
	{
		data->player.dirY = 0;
		data->player.dirX = 1;
		data->player.planeY = -0.66;
		data->player.planeX = 0;
	}
	else if (direction == 'W') // Смотрит на запад
	{
		data->player.dirY = -1;
		data->player.dirX = 0;
		data->player.planeY = 0;
		data->player.planeX = -0.66;
	}
	else if (direction == 'E') // Смотрит на восток
	{
		data->player.dirY = 1;
		data->player.dirX = 0;
		data->player.planeY = 0;
		data->player.planeX = 0.66;
	}
}


int key_hook(int keycode, void *param)
{
	t_cub *data = (t_cub *)param;

	if (keycode == 53)
	{
		close_window(data);
	}
	if (keycode == 13)
		move_forward(data);
	else if (keycode == 1)
		move_backward(data);
	else if (keycode == 0)
		move_left(data);
	else if (keycode == 2)
		move_right(data);
	else if (keycode == 123)
		rotate_left(data);
	else if (keycode == 124)
		rotate_right(data);
	return (0);
}

int	close_window(void *param)
{
	t_cub *data = (t_cub *)param;

	if (data->mlx_ptr && data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free_data(data);
		system ("leaks cub3D");
		exit(0);
	}
	return (1);
}
void	initialize_texture_addresses(t_cub *data)
{
	data->s->addr = (int *)mlx_get_data_addr(data->s->img, &data->s->bpp, \
		&data->s->size_line, &data->s->endian);
	data->w->addr = (int *)mlx_get_data_addr(data->w->img, &data->w->bpp, \
		&data->w->size_line, &data->w->endian);
	data->n->addr = (int *)mlx_get_data_addr(data->n->img, &data->n->bpp, \
		&data->n->size_line, &data->n->endian);
	data->e->addr = (int *)mlx_get_data_addr(data->e->img, &data->e->bpp, \
		&data->e->size_line, &data->e->endian);
}

void	init_texture(t_cub *data)
{
	data->n = malloc(sizeof(t_texture));
	data->n->img = mlx_xpm_file_to_image(data->mlx_ptr, data->north_texture, \
		&data->n->width, &data->n->height);
	data->w = malloc(sizeof(t_texture));
	data->w->img = mlx_xpm_file_to_image(data->mlx_ptr, data->west_texture, \
		&data->w->width, &data->w->height);
	data->s = malloc(sizeof(t_texture));
	data->s->img = mlx_xpm_file_to_image(data->mlx_ptr, data->south_texture, \
		&data->s->width, &data->s->height);
	data->e = malloc(sizeof(t_texture));
	data->e->img = mlx_xpm_file_to_image(data->mlx_ptr, data->east_texture, \
		&data->e->width, &data->e->height);
	if (data->n->img == NULL || data->w->img == NULL || \
		data->s->img == NULL || data->e->img == NULL)
	{
		free_textures_on_error(data);
		ft_exit(data, "Error\n Failed to load textures", 1);
	}
	initialize_texture_addresses(data);
	return ;
}


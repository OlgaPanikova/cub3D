/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture_key_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:47:39 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 19:00:46 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_hook_animals(int keycode, t_cub *data)
{
	if (keycode == 13)
		move_forward(data);
	else if (keycode == 1)
		move_backward(data);
	else if (keycode == 0)
		move_left(data);
	else if (keycode == 2)
		move_right(data);
}

int	key_hook(int keycode, void *param)
{
	t_cub	*data;

	data = (t_cub *)param;
	data->is_moving = 0;
	if (keycode == 53)
	{
		close_window(data);
	}
	if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
	{
		data->is_moving = 1;
		key_hook_animals(keycode, data);
	}
	else if (keycode == 123)
		rotate_left(data);
	else if (keycode == 124)
		rotate_right(data);
	return (0);
}

int	close_window(void *param)
{
	t_cub	*data;

	data = (t_cub *)param;
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

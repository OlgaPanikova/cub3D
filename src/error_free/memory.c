/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:28:16 by mgreshne          #+#    #+#             */
/*   Updated: 2024/10/04 12:30:41 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_textures_on_error(t_cub *data)
{
	if (data->n && data->n->img)
		mlx_destroy_image(data->mlx_ptr, data->n->img);
	if (data->w && data->w->img)
		mlx_destroy_image(data->mlx_ptr, data->w->img);
	if (data->s && data->s->img)
		mlx_destroy_image(data->mlx_ptr, data->s->img);
	if (data->e && data->e->img)
		mlx_destroy_image(data->mlx_ptr, data->e->img);
	if (data->n)
		free(data->n);
	if (data->w)
		free(data->w);
	if (data->s)
		free(data->s);
	if (data->e)
		free(data->e);
}

void	free_data(t_cub *data)
{
	int	i;

	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->east_texture)
		free(data->east_texture);
	free_textures_on_error(data);
	if (data->map)
	{
		i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	free(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:01:37 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 18:53:22 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_player_sprites(t_cub *data)
{
	data->sprites[0] = mlx_xpm_file_to_image(data->mlx_ptr, data->hand1,
			&data->sprite_width, &data->sprite_height);
	data->sprites[1] = mlx_xpm_file_to_image(data->mlx_ptr, data->hand2,
			&data->sprite_width, &data->sprite_height);
	if (!data->sprites[0] || !data->sprites[1])
		ft_exit(data, "Error loading player sprites", 1);
}

void	update_player_animation(t_cub *data)
{
	if (data->is_moving)
	{
		data->anim_time++;
		if (data->anim_time >= 5)
		{
			data->sprite_index = (data->sprite_index + 1) % 2;
			data->anim_time = 0;
		}
	}
	else
	{
		data->sprite_index = 0;
		data->anim_time = 0;
	}
}

void	render_player(t_cub *data)
{
	void	*current_sprite;
	int		x;
	int		y;

	x = 580;
	y = 557;
	current_sprite = data->sprites[data->sprite_index];
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, current_sprite, x, y);
}
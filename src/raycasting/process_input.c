/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:49:25 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 13:52:36 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_cub *data)
{
	if (data->map[(int)(data->player.pos_x + data->player.dir_x * \
		data->player.moveSpeed)][(int)data->player.pos_y] != '1')
		data->player.pos_x += data->player.dir_x * data->player.moveSpeed;
	if (data->map[(int)data->player.pos_x][(int)(data->player.pos_y + \
		data->player.dir_y * data->player.moveSpeed)] != '1')
		data->player.pos_y += data->player.dir_y * data->player.moveSpeed;
	start_raycast(data);
}

void	move_backward(t_cub *data)
{
	if (data->map[(int)(data->player.pos_x - data->player.dir_x * \
		data->player.moveSpeed)][(int)data->player.pos_y] != '1')
		data->player.pos_x -= data->player.dir_x * data->player.moveSpeed;
	if (data->map[(int)data->player.pos_x][(int)(data->player.pos_y - \
		data->player.dir_y * data->player.moveSpeed)] != '1')
		data->player.pos_y -= data->player.dir_y * data->player.moveSpeed;
	start_raycast(data);
}

void	move_right(t_cub *data)
{
	if (data->map[(int)(data->player.pos_x + data->player.dir_y * \
		data->player.moveSpeed)][(int)data->player.pos_y] != '1')
		data->player.pos_x += data->player.dir_y * data->player.moveSpeed;
	if (data->map[(int)data->player.pos_x][(int)(data->player.pos_y - \
		data->player.dir_x * data->player.moveSpeed)] != '1')
		data->player.pos_y -= data->player.dir_x * data->player.moveSpeed;
	start_raycast(data);
}

void	move_left(t_cub *data)
{
	if (data->map[(int)(data->player.pos_x - data->player.dir_y * \
		data->player.moveSpeed)][(int)data->player.pos_y] != '1')
		data->player.pos_x -= data->player.dir_y * data->player.moveSpeed;
	if (data->map[(int)data->player.pos_x][(int)(data->player.pos_y + \
		data->player.dir_x * data->player.moveSpeed)] != '1')
		data->player.pos_y += data->player.dir_x * data->player.moveSpeed;
	start_raycast(data);
}

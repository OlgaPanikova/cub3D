/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_rotate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:06:43 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 14:02:35 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_right(t_cub *data)
{
	data->player.olddirx = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-data->player.rot_speed)
		- data->player.dir_y * sin(-data->player.rot_speed);
	data->player.dir_y = data->player.olddirx * sin(-data->player.rot_speed)
		+ data->player.dir_y * cos(-data->player.rot_speed);
	data->player.oldplanex = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-data->player.rot_speed)
		- data->player.plane_y * sin(-data->player.rot_speed);
	data->player.plane_y = data->player.oldplanex * sin(-data->player.rot_speed)
		+ data->player.plane_y * cos(-data->player.rot_speed);
	start_raycast(data);
}

void	rotate_left(t_cub *data)
{
	data->player.olddirx = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(data->player.rot_speed)
		- data->player.dir_y * sin(data->player.rot_speed);
	data->player.dir_y = data->player.olddirx * sin(data->player.rot_speed)
		+ data->player.dir_y * cos(data->player.rot_speed);
	data->player.oldplanex = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(data->player.rot_speed)
		- data->player.plane_y * sin(data->player.rot_speed);
	data->player.plane_y = data->player.oldplanex * sin(data->player.rot_speed)
		+ data->player.plane_y * cos(data->player.rot_speed);
	start_raycast(data);
}

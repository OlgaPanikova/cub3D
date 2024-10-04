/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_rotate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:06:43 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 13:52:20 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_right(t_cub *data)
{
	data->player.olddirx = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-data->player.rotSpeed)
		- data->player.dir_y * sin(-data->player.rotSpeed);
	data->player.dir_y = data->player.olddirx * sin(-data->player.rotSpeed)
		+ data->player.dir_y * cos(-data->player.rotSpeed);
	data->player.oldplanex = data->player.planeX;
	data->player.planeX = data->player.planeX * cos(-data->player.rotSpeed)
		- data->player.planeY * sin(-data->player.rotSpeed);
	data->player.planeY = data->player.oldplanex * sin(-data->player.rotSpeed)
		+ data->player.planeY * cos(-data->player.rotSpeed);
	start_raycast(data);
}

void	rotate_left(t_cub *data)
{
	data->player.olddirx = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(data->player.rotSpeed)
		- data->player.dir_y * sin(data->player.rotSpeed);
	data->player.dir_y = data->player.olddirx * sin(data->player.rotSpeed)
		+ data->player.dir_y * cos(data->player.rotSpeed);
	data->player.oldplanex = data->player.planeX;
	data->player.planeX = data->player.planeX * cos(data->player.rotSpeed)
		- data->player.planeY * sin(data->player.rotSpeed);
	data->player.planeY = data->player.oldplanex * sin(data->player.rotSpeed)
		+ data->player.planeY * cos(data->player.rotSpeed);
	start_raycast(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_rotate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:06:43 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 12:56:12 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_right(t_cub *data)
{
	data->player.olddirx = data->player.dirX;
	data->player.dirX = data->player.dirX * cos(-data->player.rotSpeed)
		- data->player.dirY * sin(-data->player.rotSpeed);
	data->player.dirY = data->player.olddirx * sin(-data->player.rotSpeed)
		+ data->player.dirY * cos(-data->player.rotSpeed);
	data->player.oldplanex = data->player.planeX;
	data->player.planeX = data->player.planeX * cos(-data->player.rotSpeed)
		- data->player.planeY * sin(-data->player.rotSpeed);
	data->player.planeY = data->player.oldplanex * sin(-data->player.rotSpeed)
		+ data->player.planeY * cos(-data->player.rotSpeed);
	start_raycast(data);
}

void	rotate_left(t_cub *data)
{
	data->player.olddirx = data->player.dirX;
	data->player.dirX = data->player.dirX * cos(data->player.rotSpeed)
		- data->player.dirY * sin(data->player.rotSpeed);
	data->player.dirY = data->player.olddirx * sin(data->player.rotSpeed)
		+ data->player.dirY * cos(data->player.rotSpeed);
	data->player.oldplanex = data->player.planeX;
	data->player.planeX = data->player.planeX * cos(data->player.rotSpeed)
		- data->player.planeY * sin(data->player.rotSpeed);
	data->player.planeY = data->player.oldplanex * sin(data->player.rotSpeed)
		+ data->player.planeY * cos(data->player.rotSpeed);
	start_raycast(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:49:25 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 12:59:49 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_cub *data)
{
	if (data->map[(int)(data->player.posX + data->player.dirX * \
		data->player.moveSpeed)][(int)data->player.posY] != '1')
		data->player.posX += data->player.dirX * data->player.moveSpeed;
	if (data->map[(int)data->player.posX][(int)(data->player.posY + \
		data->player.dirY * data->player.moveSpeed)] != '1')
		data->player.posY += data->player.dirY * data->player.moveSpeed;
	start_raycast(data);
}

void	move_backward(t_cub *data)
{
	if (data->map[(int)(data->player.posX - data->player.dirX * \
		data->player.moveSpeed)][(int)data->player.posY] != '1')
		data->player.posX -= data->player.dirX * data->player.moveSpeed;
	if (data->map[(int)data->player.posX][(int)(data->player.posY - \
		data->player.dirY * data->player.moveSpeed)] != '1')
		data->player.posY -= data->player.dirY * data->player.moveSpeed;
	start_raycast(data);
}

void	move_right(t_cub *data)
{
	if (data->map[(int)(data->player.posX + data->player.dirY * \
		data->player.moveSpeed)][(int)data->player.posY] != '1')
		data->player.posX += data->player.dirY * data->player.moveSpeed;
	if (data->map[(int)data->player.posX][(int)(data->player.posY - \
		data->player.dirX * data->player.moveSpeed)] != '1')
		data->player.posY -= data->player.dirX * data->player.moveSpeed;
	start_raycast(data);
}

void	move_left(t_cub *data)
{
	if (data->map[(int)(data->player.posX - data->player.dirY * \
		data->player.moveSpeed)][(int)data->player.posY] != '1')
		data->player.posX -= data->player.dirY * data->player.moveSpeed;
	if (data->map[(int)data->player.posX][(int)(data->player.posY + \
		data->player.dirX * data->player.moveSpeed)] != '1')
		data->player.posY += data->player.dirX * data->player.moveSpeed;
	start_raycast(data);
}

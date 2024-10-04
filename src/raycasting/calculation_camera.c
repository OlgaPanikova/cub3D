/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:05:06 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/04 13:52:11 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculations_camera2(t_cub *data, char direction)
{
	if (direction == 'W')
	{
		data->player.dir_y = -1;
		data->player.dir_x = 0;
		data->player.planeY = 0;
		data->player.planeX = -0.66;
	}
	else if (direction == 'E')
	{
		data->player.dir_y = 1;
		data->player.dir_x = 0;
		data->player.planeY = 0;
		data->player.planeX = 0.66;
	}
}

void	calculations_camera(t_cub *data, char direction)
{
	if (direction == 'N')
	{
		data->player.dir_y = 0;
		data->player.dir_x = -1;
		data->player.planeY = 0.66;
		data->player.planeX = 0;
	}
	else if (direction == 'S')
	{
		data->player.dir_y = 0;
		data->player.dir_x = 1;
		data->player.planeY = -0.66;
		data->player.planeX = 0;
	}
	else if (direction == 'W' || direction == 'E')
		calculations_camera2(data, direction);
}

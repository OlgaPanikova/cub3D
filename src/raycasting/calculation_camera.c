/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:05:06 by opanikov          #+#    #+#             */
/*   Updated: 2024/10/03 20:05:56 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculations_camera2(t_cub *data, char direction)
{
	if (direction == 'W')
	{
		data->player.dirY = -1;
		data->player.dirX = 0;
		data->player.planeY = 0;
		data->player.planeX = -0.66;
	}
	else if (direction == 'E')
	{
		data->player.dirY = 1;
		data->player.dirX = 0;
		data->player.planeY = 0;
		data->player.planeX = 0.66;
	}
}

void	calculations_camera(t_cub *data, char direction)
{
	if (direction == 'N')
	{
		data->player.dirY = 0;
		data->player.dirX = -1;
		data->player.planeY = 0.66;
		data->player.planeX = 0;
	}
	else if (direction == 'S')
	{
		data->player.dirY = 0;
		data->player.dirX = 1;
		data->player.planeY = -0.66;
		data->player.planeX = 0;
	}
	else if (direction == 'W' || direction == 'E')
		calculations_camera2(data, direction);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:49:25 by opanikov          #+#    #+#             */
/*   Updated: 2024/09/28 22:00:27 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_space_free(t_cub *data)
{
	int	newX;
	int	newY;

	newX = (int)data->player.newX;
	newY = (int)data->player.newY;

	if (newX >= 0 && newX < data->w && newY >= 0 && newY < data->h)
		return map[newX][newY] == 0; // Убедись, что внутри карты и нет стены
	return (0);
}

void	move_forward(t_cub *data)
{
	data->player.newX = data->player.posX + data->player.dirX * data->player.moveSpeed;
	data->player.newY = data->player.posY + data->player.dirY * data->player.moveSpeed;

	if (is_space_free(data))
	{
        // Проверяем, не слишком ли близко игрок к стене по оси X
		if (map[(int)(data->player.newX + data->player.dirX * 0.1)][(int)data->player.posY] == 0)
			data->player.posX = data->player.newX;
        // Проверяем, не слишком ли близко игрок к стене по оси Y
		if (map[(int)data->player.posX][(int)(data->player.newY + data->player.dirY * 0.1)] == 0)
			data->player.posY = data->player.newY;
	}
}
void	move_backward(t_cub *data)
{
	data->player.newX = data->player.posX - data->player.dirX * data->player.moveSpeed;
	data->player.newY = data->player.posY - data->player.dirY * data->player.moveSpeed;

	if (is_space_free(data))
	{
		if (map[(int)(data->player.newX - data->player.dirX * 0.1)][(int)data->player.posY] == 0)
			data->player.posX = data->player.newX;
		if (map[(int)data->player.posX][(int)(data->player.newY - data->player.dirY * 0.1)] == 0)
			data->player.posY = data->player.newY;
	}
}

void	move_right(t_data *data)
{
	data->player.newX = data->player.posX + data->player.dirY * data->player.moveSpeed;
	data->player.newY = data->player.posY - data->player.dirX * data->player.moveSpeed;

	if (is_space_free(data))
	{
        // Проверяем коллизии для оси X с корректным использованием вектора бокового движения
		if (map[(int)(data->player.newX + data->player.dirY * 0.1)][(int)data->player.posY] == 0)
			data->player.posX = data->player.newX;
        // Проверяем коллизии для оси Y с корректным использованием вектора бокового движения
		if (map[(int)data->player.posX][(int)(data->player.newY - data->player.dirX * 0.1)] == 0)
			data->player.posY = data->player.newY;
	}
}
void move_left(t_data *data)
{
	data->player.newX = data->player.posX - data->player.dirY * data->player.moveSpeed;
	data->player.newY = data->player.posY + data->player.dirX * data->player.moveSpeed;

	if (is_space_free(data))
	{
        // Проверяем коллизии для оси X с корректным использованием вектора бокового движения
		if (map[(int)(data->player.newX - data->player.dirY * 0.1)][(int)data->player.posY] == 0)
			data->player.posX = data->player.newX;
        // Проверяем коллизии для оси Y с корректным использованием вектора бокового движения
		if (map[(int)data->player.posX][(int)(data->player.newY + data->player.dirX * 0.1)] == 0)
			data->player.posY = data->player.newY;
	}
}

void rotate_left(t_data *data)
{
	double	oldDirX;

	oldDirX = data->player.dirX;
	data->player.dirX = data->player.dirX * COS_ROT - data->player.dirY * (-SIN_ROT);
	data->player.dirY = oldDirX * (-SIN_ROT) + data->player.dirY * COS_ROT;

	double oldPlaneX = data->player.planeX;
	data->player.planeX = data->player.planeX * COS_ROT - data->player.planeY * (-SIN_ROT);
	data->player.planeY = oldPlaneX * (-SIN_ROT) + data->player.planeY * COS_ROT;
}

void rotate_right(t_data *data)
{
	double	oldDirX;

	oldDirX = data->player.dirX;
	data->player.dirX = data->player.dirX * COS_ROT - data->player.dirY * SIN_ROT;
	data->player.dirY = oldDirX * SIN_ROT + data->player.dirY * COS_ROT;

	double oldPlaneX = data->player.planeX;
	data->player.planeX = data->player.planeX * COS_ROT - data->player.planeY * SIN_ROT;
	data->player.planeY = oldPlaneX * SIN_ROT + data->player.planeY * COS_ROT;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:48:16 by opanikov          #+#    #+#             */
/*   Updated: 2024/09/29 15:44:27 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void render_wall_slice(t_cub *data, int x, int drawStart, int drawEnd, int texX, double texPos, double step, int *texture_data)
{
	int	y;
	int	texY;
	unsigned int color;

	y = drawStart;
	while (y < drawEnd)
	{
		texY = (int)texPos % texHeight;
		texPos += step;
		color = texture_data[texHeight * texY + texX];
		data->img_data[y * data->w + x] = color;
		y++;
	}
}

double calculate_texture_step(int lineHeight)
{
	return 1.0 * texHeight / lineHeight;
}

double calculate_initial_texture_position(int drawStart, int lineHeight, int sHeight)
{
	return (drawStart - sHeight / 2 + lineHeight / 2) * calculate_texture_step(lineHeight);
}
int *select_texture(t_cub *data, double wallX, int *texX)
{
	int *texture_data;

	*texX = (int)(wallX * texWidth);
	if (data->ray.side == 0)  // Столкновение с вертикальной стеной (восток или запад)
	{
		if (data->ray.rayDirX > 0) // Восточная стена (EA)
		{
			*texX = texWidth - *texX - 1;
			texture_data = (int *)mlx_get_data_addr(data->textures[0], &data->bpp, &data->size_line, &data->endian);
		}
		else  // Западная стена (WE)
			texture_data = (int *)mlx_get_data_addr(data->textures[2], &data->bpp, &data->size_line, &data->endian);
	}
	else  // Столкновение с горизонтальной стеной (север или юг)
	{
		if (data->ray.rayDirY > 0) // Северная стена (NO)
			texture_data = (int *)mlx_get_data_addr(data->textures[3], &data->bpp, &data->size_line, &data->endian);
		else  // Южная стена (SO)
		{
			*texX = texWidth - *texX - 1;
			texture_data = (int *)mlx_get_data_addr(data->textures[1], &data->bpp, &data->size_line, &data->endian);
		}
	}
	return texture_data;
}
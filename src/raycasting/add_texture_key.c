/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:47:39 by opanikov          #+#    #+#             */
/*   Updated: 2024/09/28 18:26:24 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(void *param)
{
	t_cub	*data = (t_data *)param;

	if (data->mlx_ptr && data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		// ДОБАВИТЬ ОЧИСТКУ ПАМЯТИ
		exit(0);
	}
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_KeyState *keys = (t_KeyState *)param;

	if (keycode == 53)
	{
		mlx_destroy_window(keys->data->mlx_ptr, keys->data->win_ptr); // Закрытие окна
        //ДОБАЧИТЬ ОЧИСТКУ ПАМЯТИ 
		exit(0); // Выход из программы
	}
	if (keycode == 13)
		keys->up = 1;
	else if (keycode == 1)
		keys->down = 1;
	else if (keycode == 0)
		keys->left = 1;
	else if (keycode == 2)
		keys->right = 1;
	else if (keycode == 124)
		keys->pov_left = 1;
	else if (keycode == 123)
		keys->pov_right = 1;
	return (0);
}

int	key_release_hook(int keycode, void *param)
{
	t_KeyState *keys = (t_KeyState *)param;

	if (keycode == 13)
		keys->up = 0;
	if (keycode == 1)
		keys->down = 0;
	if (keycode == 0)
		keys->left = 0;
	if (keycode == 2)
		keys->right = 0;
	if (keycode == 124)
		keys->pov_left = 0;
	if (keycode == 123)
		keys->pov_right = 0;
	return (0);
}
void	*file_to_image(t_cub *data, char *textures_path)
{
	int		img_w;
	int		img_h;
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx_ptr, textures_path, &img_w, &img_h);
	if (!img)
	{
		printf(stderr, "Ошибка загрузки изображения: %s\n", textures_path); // очистить память 
		exit(EXIT_FAILURE); // Выход из программы при ошибке
	}
	return (img);
}

void	init_texture(t_cub *data)
{
	data->textures[0] = file_to_image(data, data->north_texture);
	data->textures[1] = file_to_image(data, data->south_texture);
	data->textures[2]= file_to_image(data, data->west_texture);
	data->textures[3] = file_to_image(data, data->east_texture);
}


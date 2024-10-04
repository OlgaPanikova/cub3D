/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:07:22 by mgreshne          #+#    #+#             */
/*   Updated: 2024/10/04 14:02:35 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_mlx(t_cub *data)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		ft_exit(data, "Error\n Failed to initialize MiniLibX\n", 1);
	win_ptr = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
	if (!win_ptr)
	{
		ft_exit(data, "Error\n Failed to initialize MiniLibX\n", 1);
	}
	data->mlx_ptr = mlx_ptr;
	data->win_ptr = win_ptr;
}

void	init_data(t_cub *data)
{
	int	i;

	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->player.move_speed = MOVE_SPEED;
	data->player.rot_speed = ROT_SPEED;
	i = -1;
	while (++i < 3)
	{
		data->floor_color[i] = -1;
		data->ceiling_color[i] = -1;
	}
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->wight_screen = SCREEN_WIDTH;
	data->hight_screen = SCREEN_HEIGHT;
}

int	mouse_move(int x, int y, t_cub *data)
{
	mlx_mouse_hide();
	mlx_mouse_get_pos(data->win_ptr, &x, &y);
	if (x > data->wight_screen / 2)
		key_hook(124, data);
	if (x < data->wight_screen / 2)
		key_hook(123, data);
	mlx_mouse_move(data->win_ptr, data->wight_screen / 2, y / 2);
	return (0);
}

int	main(int args, char **argv)
{
	t_cub	*data;

	data = malloc(sizeof(t_cub));
	if (!data)
		return (ft_print_error("Failed to allocate memory\n", 1));
	if (args != 2)
		return (ft_print_error("Error arguments\n", 1));
	if (!check_file_extension(argv[1]))
		return (ft_print_error("Error: File must have a .cub extension\n", 1));
	init_data(data);
	init_mlx(data);
	if (parsing_args(data, argv[1]) != 0)
	{
		free_data(data);
		return (1);
	}
	rgb_to_hex(data); // цвета приводим к одному значению!!
	init_texture(data);
	calculations_camera(data, data->direction);
	start_raycast(data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win_ptr, 17, 0L, close_window, data);
	mlx_loop(data->mlx_ptr);
	free_data(data);
	// system ("leaks cub3D");
	return (0);
}

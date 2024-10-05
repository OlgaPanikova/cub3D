/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:07:22 by mgreshne          #+#    #+#             */
/*   Updated: 2024/10/05 18:20:01 by opanikov         ###   ########.fr       */
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
	win_ptr = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!win_ptr)
	{
		ft_exit(data, "Error\n Failed to initialize MiniLibX\n", 1);
	}
	data->mlx_ptr = mlx_ptr;
	data->win_ptr = win_ptr;
}

void	init_data2(t_cub *data)
{
	data->wight_screen = SCREEN_WIDTH;
	data->hight_screen = SCREEN_HEIGHT;
	data->n = NULL;
	data->w = NULL;
	data->s = NULL;
	data->e = NULL;
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
	init_data2(data);
}

int	main(int args, char **argv)
{
	t_cub	*data;

	data = malloc(sizeof(t_cub));
	if (!data)
		return (ft_print_error("Failed to allocate memory\n", 1));
	if (args != 2)
	{
		free(data);
		printf("Error arguments\n");
		system("leaks cub3D");
		exit(1);
	}
	if (!check_file_extension(argv[1]))
		ft_exit(data, "Error\nFile must have a .cub extension", 1);
	init_data(data);
	if (parsing_args(data, argv[1]) != 0)
		return (free_data(data), 1);
	rgb_to_hex(data);
	init_mlx(data);
	init_texture(data);
	calculations_camera(data, data->direction);
	start_raycast(data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win_ptr, 17, 0L, close_window, data);
	mlx_loop(data->mlx_ptr);
	free_data(data);
	return (0);
}

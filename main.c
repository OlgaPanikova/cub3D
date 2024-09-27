/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:07:22 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/23 23:35:05 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_map(char **map) {
    int i = 0;

    // Пока текущий указатель (строка) не равен NULL
    while (map[i] != NULL) {
        int j = 0;

        // Пока не достигнем конца строки (символ '\0')
        while (map[i][j] != '\0') {
            printf("[%c] ", map[i][j]);
            j++;
        }
        printf("\n"); // Переход на новую строку после вывода всей строки
        i++;
    }
}



void	init_data(t_cub *data)
{
	int	i;

	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	i = -1;
	while (++i < 3)
	{
		data->floor_color[i] =0;
		data->ceiling_color[i] = 0;
	}
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
}


int main(int args, char **argv)
{
	t_cub	data;

	if (args != 2)
		return (ft_print_error("Error arguments\n", 1));
	if (!check_file_extension(argv[1]))
		return (ft_print_error("Error: File must have a .cub extension\n", 1));
	init_data(&data);
	if (parsing_args(&data, argv[1]) != 0)
	{
		free_data(&data);
		return (1);
	}

	rgb_to_hex(&data); // цвета приводим к одному значению!!

	printf("North texture: %s\n", data.north_texture);
	printf("South texture: %s\n", data.south_texture);
	printf("West texture: %s\n", data.west_texture);
	printf("East texture: %s\n", data.east_texture);
	printf("Floor color: %d,%d,%d\n", data.floor_color[0], data.floor_color[1], data.floor_color[2]);
	printf("Ceiling color: %d,%d,%d\n", data.ceiling_color[0], data.ceiling_color[1], data.ceiling_color[2]);


	print_map(data.map);

	free_data(&data);
	return (0);
}



#include "cub3D.h"


int	ft_flood_fill(t_cub *data, int y, int x)
{
	// Проверяем, вышли ли мы за пределы карты
	if (y < 0 || y >= data->map_height || x < 0 ) // || x >= data->window_width или как ?
	{
		ft_print_error("Error: карта не окружена стенами\n", 1);
		return (1); // ошибка, если вышли за пределы карты
	}
	// Если текущая клетка - стена, возвращаем 0, так как это не ошибка
	if (data->map[y][x] == '1')
		return (0);
	// Если текущая клетка уже обработана, ничего не делаем
	if (data->map[y][x] == '+')
		return (0);
	// Если текущая клетка - проходимая (0), отмечаем её как обработанную
	if (data->map[y][x] == '0' || data->map[y][x] == 'N')
		data->map[y][x] = '+';

	// Рекурсивно проверяем соседние клетки
	if (ft_flood_fill(data, y - 1, x) == 1) // вверх
		return (1);
	if (ft_flood_fill(data, y + 1, x) == 1) // вниз
		return (1);
	if (ft_flood_fill(data, y, x - 1) == 1) // влево
		return (1);
	if (ft_flood_fill(data, y, x + 1) == 1) // вправо
		return (1);

	return (0); // если ошибок не найдено
}

int	ft_check_flood_fill(t_cub *data)
{
	if (ft_flood_fill(data, data->pos_y, data->pos_x) == 0)
	{
		printf("Карта окружена стенами!\n");
	}
	else
	{
		ft_print_error("Ошибка: карта не окружена стенами!\n", 1);
		return (1);
	}
	return (0);
}


int	check_map(t_cub *data)
{
	int		i;
	size_t	j;
	int player_found;
	size_t len;

	i = 0;
	player_found = 0;
	while (i < data->map_height)
	{
		j = 0;
		len = strlen(data->map[i]);
		while (j < len)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W' || data->map[i][j] == 'E' || data->map[i][j] == 'S')
			{
				if (player_found)
					return (ft_print_error("Error: Multiple player positions in map\n", 1));
				data->pos_x = j;
				data->pos_y = i;
				data->direction = data->map[i][j];
				player_found = 1;
				printf("Player found at (%f, %f) with direction %c\n", data->pos_x, data->pos_y, data->direction);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		return (ft_print_error("Error: No player position in map\n", 1));
	else
		printf("vse OKKK\n");
	return (0);
}

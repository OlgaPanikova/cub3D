/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:36:26 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/23 22:30:16 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void print_first_line(char **map) {
    if (map == NULL || map[0] == NULL) {
        printf("Массив пуст или первая строка отсутствует.\n");
        return;
    }

    printf("Первая строка массива: %s\n", map[0]);
}

char	**add_line_to_map(char **map, int current_size, char *new_line)
{
	char	**new_map;
	int		i;

	printf("str = %s\n", new_line);

	i = 0;
	while (new_line[i] != '\0')
    {
        // Выводим числовое значение символа (его ASCII-код)
        printf("%d ", (int)new_line[i]);
        i++;
    }
    printf("\n");



	new_map = malloc(sizeof(char *) * (current_size + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < current_size)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = strdup_until_newline(new_line);


	int j = 0;
	while (new_map[i][j] != '\0')
    {
        // Выводим числовое значение символа (его ASCII-код)
        printf("%d ", (int)new_map[i][j]);
        j++;
    }
    printf("\n");


	if (!new_map[i])
	{
		free(new_map);
		return (NULL);
	}
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}

int	is_map_line_valid(const char *line)
{
	printf("\nooooooooo\n");
	int i = 0;
	while (line[i])
	{
		printf("%d ", line[i]);
		i++;
	}
	printf("\nooooooooo\n");

	while (*line != '\0' && *line != '\n') // !!!!!!!!!!!!!! пока не конец строки
	{
		if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}

int	parse_map(t_cub *data, char *line)
{
	printf("tyt заполняется карта\n");
	data->map = add_line_to_map(data->map, data->map_height, line);
	if (!data->map)
		return (ft_print_error("Error: Memory allocation failed\n", 1));
	data->map_height++;
	return (0);
}

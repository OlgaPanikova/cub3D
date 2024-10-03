/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:22:32 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/29 19:32:42 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_after_map(int fd, t_cub *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\0' || *line == '\n' || skip_spaces(line)[0] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		close(fd);
		ft_exit(data, "Error\nThere should be nothing after the map", 1);
	}

}

int	parse_lines(t_cub *data, int fd)
{
	char	*line;
	int		is_map_parsing;
	int		elements_completed;

	is_map_parsing = 0;
	elements_completed = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_parsing && (*line == '\0' || *line == '\n'
				|| skip_spaces(line)[0] == '\0'))
			break ;
		if (process_line(data, line, &is_map_parsing, &elements_completed) != 0)
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line != NULL)
		free(line);
	return (0);
}

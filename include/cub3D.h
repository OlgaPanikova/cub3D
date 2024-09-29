/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:33:32 by mgreshne          #+#    #+#             */
/*   Updated: 2024/09/29 19:35:36 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include "get_next_line.h"
# include "libft.h"

typedef struct s_cub
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	int				floor_color[3]; // RGB
	int				ceiling_color[3]; // RGB
	unsigned int	hex_floor;
	unsigned int	hex_ceiling;
	char			**map;
	int				map_width;
	int				map_height;
	double				posX;
	double				posY;
	char			direction;   // Направление игрока (N, W, E, S)
}	t_cub;


char	*get_next_line(int fd);

int		ft_print_error(char *s, int code);

int		parse_color_line(t_cub *data, char *line);
int		parse_texture_line(t_cub *data, char *line);
int		process_line(t_cub *data, char *line, int *is_map_parsing,
			int *elements_completed);
int		parsing_args(t_cub *data, const char *file);
int		open_file(t_cub *data, const char *file);

int		parse_lines(t_cub *data, int fd);
void	check_after_map(int fd, t_cub *data);

int			parse_color(t_cub *data, int *color, char *line);
int			parse_texture(t_cub *data, char **dest, char *line, const char *identifier);
int			check_texture_files(t_cub *data);
int			check_texture_file(const char *filename);

int			is_map_line_valid(const char *line);
int			parse_map(t_cub *data, char *line);

void		free_data(t_cub *data);
void		ft_exit(t_cub *data, char *str, int i);

char		*strdup_until_newline(const char *line);
void 		rgb_to_hex(t_cub *data);
int			check_texture_extension(const char *filename);
char		*skip_spaces(char *line);
int			check_file_extension(const char *filename);

void		check_map(t_cub *data);
int			ft_check_flood_fill(t_cub *data);
void		check_walls(t_cub *data, int y, int x);


#endif

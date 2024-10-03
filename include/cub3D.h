/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:33:32 by mgreshne          #+#    #+#             */
/*   Updated: 2024/10/03 17:49:49 by opanikov         ###   ########.fr       */
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
# include "mlx.h"
# include <sys/time.h>
#include <math.h>

# define screenWidth  840
# define screenHeight 680

# define MOVE_SPEED 0.11
# define ROT_SPEED 0.07

#define texWidth 100
#define texHeight 100

typedef struct s_texture
{
	void	*img;
	int		*addr;
	char	**data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}				t_texture;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;
	double	newX;
	double	newY;
	double	olddirx;
	double	oldplanex;
} t_player;

typedef struct s_ray
{
	double	rayDirX;
	double	rayDirY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		side;
	double	perpWallDist;
	double	wallx;
	double	cameraX;
	int		hit;
} t_ray;

typedef struct s_cub
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	int				floor_color[3];
	int				ceiling_color[3];
	unsigned int	hex_floor;
	unsigned int	hex_ceiling;
	char			**map;
	int				map_width;
	int				map_height;
	char			direction;
	void			*mlx_ptr;
	void			*win_ptr;
	int				wight_screen;
	int				hight_screen;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				texx;
	int				texy;
	int				texheight;
	int				color;
	t_player		player;
	t_ray			ray;
	t_texture		*n;
	t_texture		*w;
	t_texture		*s;
	t_texture		*e;
	t_texture		*image;
	t_texture		*wallt;
}	t_cub;


char		*get_next_line(int fd);

int			ft_print_error(char *s, int code);

int			check_file_extension(const char *filename);
int			parse_color_line(t_cub *data, char *line);
int			parse_texture_line(t_cub *data, char *line);
int			process_line(t_cub *data, char *line, int *is_map_parsing,
				int *elements_completed);
int			parsing_args(t_cub *data, const char *file);

char		*skip_spaces(char *line);
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

int			check_map(t_cub *data);
int			ft_check_flood_fill(t_cub *data);
int			check_walls(t_cub *data, int y, int x);

void		init_data(t_cub *data);
void		init_mlx(t_cub *data);

void		start_raycast(t_cub *data);
void		render(t_cub *data);
void		calculate_ray_direction(t_cub *data, int x);

void		calculate_initial_step(t_cub *data);
void		detect_wall_hit(t_cub *data);
void		calculate_wall_rendering(t_cub *data);
void		side_of_the_wall(t_cub *data);
void		draw_wall(t_cub *data, int x);

void		move_forward(t_cub *data);
void		move_backward(t_cub *data);
void		move_right(t_cub *data);
void		move_left(t_cub *data);
void		rotate_right(t_cub *data);
void		rotate_left(t_cub *data);

void		draw_floor_and_ceiling(t_cub *data);
void		draw_floor(t_cub *data);
void		draw_ceiling(t_cub *data);

void		init_texture(t_cub *data);
void		initialize_texture_addresses(t_cub *data);
int			close_window(void *param);
int			key_hook(int keycode, void *param);
void		calculations_camera(t_cub *data, char direction);

void		free_textures_on_error(t_cub *data);

#endif

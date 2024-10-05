/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:33:32 by mgreshne          #+#    #+#             */
/*   Updated: 2024/10/05 15:56:01 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <ctype.h>
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <sys/time.h>
# include <math.h>

# define SCREEN_WIDTH 840
# define SCREEN_HEIGHT 680

# define MOVE_SPEED 0.11
# define ROT_SPEED 0.07

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
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	double	olddirx;
	double	oldplanex;
}	t_player;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	double	wallx;
	double	camera_x;
	int		hit;
}	t_ray;

typedef struct s_cub
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*hand1;
	char			*hand2;
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
	void			*sprites[2];
	int				sprite_index;
	int				anim_time;
	int				is_moving;
	int				sprite_width;
	int				sprite_height;
	int				fd;
}	t_cub;

char		*get_next_line(int fd);

int			ft_print_error(char *s, int code);

int			check_file_extension(const char *filename);
int			parse_color_line(t_cub *data, char *line);
int			parse_texture_line(t_cub *data, char *line);
int			process_line(t_cub *data, char *line, int *is_map_parsing,
				int *elements_completed);
int			parsing_args(t_cub *data, const char *file);
int			parse_color_line(t_cub *data, char *line);
int			parse_texture_line(t_cub *data, char *line);
int			process_line(t_cub *data, char *line, int *is_map_parsing,
				int *elements_completed);
int			parsing_args(t_cub *data, const char *file);
int			open_file(t_cub *data, const char *file);

int			parse_lines(t_cub *data, int fd);
void		check_after_map(int fd, t_cub *data);

int			parse_color(t_cub *data, int *color, char *line);
int			parse_texture(t_cub *data, char **dest, char *line,
				const char *identifier);
int			check_texture_files(t_cub *data);
int			check_texture_file(t_cub *data, const char *filename);

int			is_map_line_valid(const char *line);
int			parse_map(t_cub *data, char *line);

void		free_data(t_cub *data);
void		ft_exit(t_cub *data, char *str, int i);

char		*strdup_until_newline(const char *line);
void		rgb_to_hex(t_cub *data);
int			check_texture_extension(const char *filename);
char		*skip_spaces(char *line);
int			check_file_extension(const char *filename);

void		check_map(t_cub *data);
int			ft_check_flood_fill(t_cub *data);
void		check_walls(t_cub *data, int y, int x);

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
void		calculations_camera2(t_cub *data, char direction);

void		free_textures_on_error(t_cub *data);

void		render_player(t_cub *data);
void		update_player_animation(t_cub *data);
void		load_player_sprites(t_cub *data);

int			mouse_move(int x, int y, t_cub *data);
void		free_mlx(t_cub *data);

#endif

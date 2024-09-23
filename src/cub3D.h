/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:54:14 by lelichik          #+#    #+#             */
/*   Updated: 2024/09/23 21:01:51 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define screenWidth 840 //размеры экрана
# define screenHeight 680

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

#define COS_ROT 0.996
#define SIN_ROT 0.087

#define texWidth 100
#define texHeight 100

typedef struct {
    int r;
    int g;
    int b;
} ColorRGB;

typedef struct s_key
{
    int up;
    int down;
    int right;
    int left;
    int pov_left;
    int pov_right;
    struct s_data *data;
} t_KeyState;

typedef struct s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    double moveSpeed;
    double rotSpeed;
    double newX;
    double newY;
} t_player;

typedef struct s_ray
{
    double rayDirX;
    double rayDirY;
    double deltaDistX;
    double deltaDistY;
    double sideDistX;
    double sideDistY;
    int mapX;
    int mapY;
    int stepX;
    int stepY;
    int side;
    double perpWallDist;
} t_ray;

typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    t_KeyState *keys;
    t_player player;
    t_ray ray;
    int w;
    int h;
    int bpp;
    int size_line;
    int endian;
    void *img;
    int *img_data;
    void *textures[4];
    char *textures_path[4];
} t_data;


#endif

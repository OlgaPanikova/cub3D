/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:54:14 by lelichik          #+#    #+#             */
/*   Updated: 2024/09/17 17:19:19 by lelichik         ###   ########.fr       */
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
#define ROT_SPEED 0.05

typedef struct {
    int r;
    int g;
    int b;
} ColorRGB;

typedef struct {
    int up;
    int down;
    int right;
    int left;
    int pov_left;
    int pov_right;
} KeyState;

typedef struct {
    void *mlx_ptr;
    void *win_ptr;
	KeyState *keys;
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    double moveSpeed;
    double rotSpeed;
    int w;
    int h;
    int bpp;
    int size_line;
    int endian;
    void *img;
    char *img_data;
} RenderData;

#endif

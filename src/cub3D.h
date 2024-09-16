/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:54:14 by lelichik          #+#    #+#             */
/*   Updated: 2024/09/16 20:36:21 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define screenWidth 640 //размеры экрана
# define screenHeight 480

typedef struct {
    int r;
    int g;
    int b;
	// int w;
	// int e;
} ColorRGB;

typedef struct {
    int up;
    int down;
    int right;
    int left;
} KeyState;

typedef struct {
    void *mlx_ptr;
    void *win_ptr;
	KeyState *keys;
    // KeyState *keys;
    // double posX;
    // double posY;
    // double dirX;
    // double dirY;
    // double planeX;
    // double planeY;
    // int w;
    // int h;
} RenderData;

#endif

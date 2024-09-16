/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:28:49 by lelichik          #+#    #+#             */
/*   Updated: 2024/09/16 20:57:33 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double absValue(double x)
{
    return (x < 0) ? -x : x;
}

unsigned int getTicks(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000); // Возвращает время в миллисекундах
}

void verLine(int x, int drawStart, int drawEnd, ColorRGB color, void *mlx_ptr, void *win_ptr) {
    for (int y = drawStart; y <= drawEnd; y++) {
        // Например, отрисовка точки с помощью функции MiniLibX (или другой библиотеки)
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, (color.r << 16) | (color.g << 8) | color.b);
    }
}

KeyState keys = {0, 0, 0, 0}; // Инициализация состояния клавиш

int key_hook(int keycode, void *param) {
    KeyState *keys = (KeyState *)param;
    
    if (keycode == 126) { // Код для стрелки вверх
        keys->up = 1;
    } else if (keycode == 125) { // Код для стрелки вниз
        keys->down = 1;
    } else if (keycode == 123) { // Код для стрелки влево
        keys->left = 1;
    } else if (keycode == 124) { // Код для стрелки вправо
        keys->right = 1;
    }
    return 0;
}

int key_release_hook(int keycode, void *param) {
    KeyState *keys = (KeyState *)param;

    if (keycode == 126) 
        keys->up = 0;
    if (keycode == 125)
        keys->down = 0;
    if (keycode == 123)
        keys->left = 0;
    if (keycode == 124)
        keys->right = 0;
    return 0;
}

int render(void *param)
{
    RenderData *data = (RenderData *)param;
    KeyState *keys = data->keys;
       // Стартовые позиции и направления
    double posX = 22, posY = 12;
    double dirX = -1, dirY = 0;
    double planeX = 0, planeY = 0.66;

    // Переменные времени
    double time = 0;
    double oldTime = 0;

   // Ширина и высота экрана
    int w = screenWidth;
    int h = screenHeight;

    for (int x = 0; x < w; x++) {
            // Вычисление позиции и направления луча
            double cameraX = 2 * x / (double)w - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            int mapX = (int)posX;
            int mapY = (int)posY;

            double sideDistX;
            double sideDistY;

            double deltaDistX = (rayDirX == 0) ? 1e30 : absValue(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : absValue(1 / rayDirY);

            double perpWallDist;
            int stepX, stepY, hit = 0, side;

            // Расчет шага и начальных значений sideDist
            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }

            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            // Обработка столкновений
            while (hit == 0) {
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if (worldMap[mapX][mapY] > 0) hit = 1;
            }

            if (side == 0)
                perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
            else
                perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

            int lineHeight = (int)(h / perpWallDist);
            int drawStart = -lineHeight / 2 + h / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + h / 2;
            if (drawEnd >= h) drawEnd = h - 1;

            ColorRGB color;
            switch (worldMap[mapX][mapY]) {
                case 1:  color = (ColorRGB){255, 0, 0};    break; // красный
                case 2:  color = (ColorRGB){0, 255, 0};    break; // зелёный
                case 3:  color = (ColorRGB){0, 0, 255};    break; // синий
                case 4:  color = (ColorRGB){255, 255, 255}; break; // белый
                default: color = (ColorRGB){255, 255, 0};   break; // жёлтый
            }

            if (side == 1) {
                color.r /= 2;
                color.g /= 2;
                color.b /= 2;
            }

            verLine(x, drawStart, drawEnd, color, data->mlx_ptr, data->win_ptr);
        }

        // Подсчет времени кадра
        oldTime = time;
        time = getTicks();
        double frameTime = (time - oldTime) / 1000.0;

        // Счетчик FPS
        // printf("%f\n", 1.0 / frameTime);


        double moveSpeed = frameTime * 5.0;
        double rotSpeed = frameTime * 3.0;


        // Движение вперёд

         if (keys->up)
        {
            if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
            if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
        }

        if (keys->down)
        {
            if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0) posX -= dirX * moveSpeed;
            if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
        }

        // Поворот вправо
         if (keys->right)
         {
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }

// Поворот влево
        if (keys->left)
        {
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }
    return 0;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;


    // Стартовые позиции и направления
    // double posX = 22, posY = 12;
    // double dirX = -1, dirY = 0;
    // double planeX = 0, planeY = 0.66;

    // // Переменные времени
    // double time = 0;
    // double oldTime = 0;

    // Ширина и высота экрана
    // int screenWidth = 640;
    // int screenHeight = 480;
    // int w = screenWidth;
    // int h = screenHeight;

    // Инициализация MiniLibX
    void *mlx_ptr = mlx_init();
    if (!mlx_ptr) {
        printf("Ошибка: не удалось инициализировать MiniLibX\n");
        return 1;
    }

    // Создание окна
    void *win_ptr = mlx_new_window(mlx_ptr, screenWidth, screenHeight, "Raycaster");
    if (!win_ptr) {
        printf("Ошибка: не удалось создать окно\n");
        return 1;
    }

    printf("Raycaster screen: %dx%d\n", screenWidth, screenHeight);


    RenderData data;
    data.mlx_ptr = mlx_ptr;
    data.win_ptr = win_ptr;
    data.keys = &keys;
    // data.posX = 22;
    // data.posY = 12;
    // data.dirX = -1;
    // data.dirY = 0;
    // data.planeX = 0;
    // data.planeY = 0.66;
    // data.w = screenWidth;
    // data.h = screenHeight;
    mlx_hook(win_ptr, 2, 1L << 0, key_hook, &keys);
    mlx_hook(win_ptr, 17, 1L << 0, key_release_hook, &keys);
    mlx_loop_hook(mlx_ptr, render, &data);
    
//     while (1) {
//         for (int x = 0; x < w; x++) {
//             // Вычисление позиции и направления луча
//             double cameraX = 2 * x / (double)w - 1;
//             double rayDirX = dirX + planeX * cameraX;
//             double rayDirY = dirY + planeY * cameraX;

//             int mapX = (int)posX;
//             int mapY = (int)posY;

//             double sideDistX;
//             double sideDistY;

//             double deltaDistX = (rayDirX == 0) ? 1e30 : absValue(1 / rayDirX);
//             double deltaDistY = (rayDirY == 0) ? 1e30 : absValue(1 / rayDirY);

//             double perpWallDist;
//             int stepX, stepY, hit = 0, side;

//             // Расчет шага и начальных значений sideDist
//             if (rayDirX < 0) {
//                 stepX = -1;
//                 sideDistX = (posX - mapX) * deltaDistX;
//             } else {
//                 stepX = 1;
//                 sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//             }

//             if (rayDirY < 0) {
//                 stepY = -1;
//                 sideDistY = (posY - mapY) * deltaDistY;
//             } else {
//                 stepY = 1;
//                 sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//             }

//             // Обработка столкновений
//             while (hit == 0) {
//                 if (sideDistX < sideDistY) {
//                     sideDistX += deltaDistX;
//                     mapX += stepX;
//                     side = 0;
//                 } else {
//                     sideDistY += deltaDistY;
//                     mapY += stepY;
//                     side = 1;
//                 }
//                 if (worldMap[mapX][mapY] > 0) hit = 1;
//             }

//             if (side == 0)
//                 perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
//             else
//                 perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

//             int lineHeight = (int)(h / perpWallDist);
//             int drawStart = -lineHeight / 2 + h / 2;
//             if (drawStart < 0) drawStart = 0;
//             int drawEnd = lineHeight / 2 + h / 2;
//             if (drawEnd >= h) drawEnd = h - 1;

//             ColorRGB color;
//             switch (worldMap[mapX][mapY]) {
//                 case 1:  color = (ColorRGB){255, 0, 0};    break; // красный
//                 case 2:  color = (ColorRGB){0, 255, 0};    break; // зелёный
//                 case 3:  color = (ColorRGB){0, 0, 255};    break; // синий
//                 case 4:  color = (ColorRGB){255, 255, 255}; break; // белый
//                 default: color = (ColorRGB){255, 255, 0};   break; // жёлтый
//             }

//             if (side == 1) {
//                 color.r /= 2;
//                 color.g /= 2;
//                 color.b /= 2;
//             }

//             verLine(x, drawStart, drawEnd, color, mlx_ptr, win_ptr);
//         }

//         // Подсчет времени кадра
//         oldTime = time;
//         time = getTicks();
//         double frameTime = (time - oldTime) / 1000.0;

//         // Счетчик FPS
//         // printf("%f\n", 1.0 / frameTime);


//         double moveSpeed = frameTime * 5.0;
//         double rotSpeed = frameTime * 3.0;


//         // Движение вперёд

//          if (keys.up) {
//             if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
//             if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
//         }

//         if (keys.down) {
//             if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0) posX -= dirX * moveSpeed;
//             if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
//         }

//         // Поворот вправо
//          if (keys.right) {
//             double oldDirX = dirX;
//             dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//             dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    
//             double oldPlaneX = planeX;
//             planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//             planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//         }

// // Поворот влево
//         if (keys.left) {
//             double oldDirX = dirX;
//             dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//             dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    
//             double oldPlaneX = planeX;
//             planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//             planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//         }
//     }

        mlx_loop(mlx_ptr);
}
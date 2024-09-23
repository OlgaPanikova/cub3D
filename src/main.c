/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:28:49 by lelichik          #+#    #+#             */
/*   Updated: 2024/09/21 18:24:34 by lelichik         ###   ########.fr       */
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

// void drawVerticalLine(int x, int drawStart, int drawEnd, ColorRGB color, t_data *data)
// {
//     for (int y = drawStart; y <= drawEnd; y++)
//     {
//         if (y >= 0 && y < data->h && x >= 0 && x < data->w) {
//             int pixel_index = (y * data->size_line) + (x * (data->bpp / 8));
//             data->img_data[pixel_index] = color.b; // Blue
//             data->img_data[pixel_index + 1] = color.g; // Green
//             data->img_data[pixel_index + 2] = color.r; // Red
//         }
//     }
// }
int key_hook(int keycode, void *param)
{
    t_KeyState *keys = (t_KeyState *)param;
    
    if (keycode == 13)
        keys->up = 1;
    else if (keycode == 1)
        keys->down = 1;
    else if (keycode == 0)
        keys->left = 1;
    else if (keycode == 2)
        keys->right = 1;
     else if (keycode == 124)
        keys->pov_left = 1;
     else if (keycode == 123)
        keys->pov_right = 1;
    return 0;
}

int key_release_hook(int keycode, void *param)
{
    t_KeyState *keys = (t_KeyState *)param;

    if (keycode == 13)
        keys->up = 0;
    if (keycode == 1)
        keys->down = 0;
    if (keycode == 0)
        keys->left = 0;
    if (keycode == 2)
        keys->right = 0;
    if (keycode == 124)
        keys->pov_left = 0;
    if (keycode == 123)
        keys->pov_right = 0;
    return 0;
}

void draw_floor_and_ceiling(t_data *data)
{
    unsigned int *pixels = (unsigned int *)data->img_data;  // Указатель на массив пикселей
    // int num_pixels = data->w * data->h;                     // Общее количество пикселей
    int half_height = data->h / 2;                          // Половина высоты для разделения экрана на потолок и пол
    unsigned int ceiling_color = 0x87CEEB;                  // Цвет потолка (можно задать любой)
    unsigned int floor_color = 0x8B4513;                    // Цвет пола (можно задать любой)

    // Отрисовка потолка (верхняя половина экрана)
    int y = 0;
    while (y < half_height)
    {
        int x = 0;
        while (x < data->w) 
        {
            pixels[y * data->w + x] = ceiling_color;
            x++;
        }
        y++;
    }

    // Отрисовка пола (нижняя половина экрана)
    int i = half_height;
    while (i < data->h)
    {
        int x = 0;
        while (x < data->w)
        {
            pixels[i * data->w + x] = floor_color;
            x++;
        }
        i++;
    }
}

void *file_to_image(t_data *data, char *textures_path)
{
    int img_w;
    int img_h;
    void *img;

    img = mlx_xpm_file_to_image(data->mlx_ptr, textures_path, &img_w, &img_h);
    if (!img)
    {
        fprintf(stderr, "Ошибка загрузки изображения: %s\n", textures_path);
        exit(EXIT_FAILURE); // Выход из программы при ошибке
    }
    return img;
}

void init_sprite(t_data *data)
{
    for (int i = 0; i < 1; ++i)
    {
        data->textures[i] = file_to_image(data, data->textures_path[i]);
    }
}

void init_sprite_path(t_data *data)
{
    data->textures_path[0] = "./1.xpm";
}

void clear_image(t_data *data)
{
    unsigned int    *pixels;
    int num_pixels;
    int i;

    i = 0;
    
    data->img = mlx_new_image(data->mlx_ptr, data->w, data->h);
    data->img_data = (int *)mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);

    //Шаг 2: Очистка изображения (фоновый цвет черный)
    pixels = (unsigned int *)data->img_data;
    num_pixels = data->w * data->h;
    while (i < num_pixels)
    {
        pixels[i] = 0x000000; // Черный цвет
        i++;
    }
}

int render(void *param)
{
    t_data *data = (t_data *)param;
    t_KeyState *keys = data->keys;

    clear_image(data);
    draw_floor_and_ceiling(data);
    
    for (int x = 0; x < data->w; x++)
    {
            // Вычисление позиции и направления луча
            double cameraX = 2 * x / (double)data->w - 1;
            double rayDirX = data->dirX + data->planeX * cameraX;
            double rayDirY = data->dirY + data->planeY * cameraX;

            int mapX = (int)data->posX;
            int mapY = (int)data->posY;

            double sideDistX;
            double sideDistY;

            double deltaDistX = (rayDirX == 0) ? 1e30 : absValue(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : absValue(1 / rayDirY);

            double perpWallDist;
            int stepX, stepY, hit = 0, side;

            // Расчет шага и начальных значений sideDist
            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (data->posX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
            }

            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (data->posY - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
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
                if (mapX >= 0 && mapX < data->w && mapY >= 0 && mapY < data->h) {
                    if (worldMap[mapX][mapY] > 0) hit = 1;
                }
            }


           if (side == 0) {
            perpWallDist = (mapX - data->posX + (1 - stepX) / 2) / rayDirX;
        } else {
            perpWallDist = (mapY - data->posY + (1 - stepY) / 2) / rayDirY;
        }

        // Высота линии для отрисовки
        int lineHeight = (int)(data->h / perpWallDist);

        // Определение начальной и конечной точки отрисовки
        int drawStart = -lineHeight / 2 + data->h / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + data->h / 2;
        if (drawEnd >= data->h) drawEnd = data->h - 1;

        // Выбор текстуры
        // int texNum = worldMap[mapX][mapY] - 1; // Подразумевается, что текстуры начинаются с 1

        // Получение данных пикселей текстуры
        int *texture_data = (int *)mlx_get_data_addr(data->textures[0], &data->bpp, &data->size_line, &data->endian);

        // Вычисление координат текстуры
        double wallX;
        if (side == 0) {
            wallX = data->posY + perpWallDist * rayDirY;
        } else {
            wallX = data->posX + perpWallDist * rayDirX;
        }
        wallX -= floor(wallX);

        int texX = (int)(wallX * texWidth);
        if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

        // Вычисление шага и начальной текстурной координаты
        double step = 1.0 * texHeight / lineHeight;
        double texPos = (drawStart - data->h / 2 + lineHeight / 2) * step;

        for (int y = drawStart; y < drawEnd; y++)
        {
            int texY = (int)texPos & (texHeight - 1); // Применение маски, чтобы избежать переполнения
            texPos += step;

            // Получение цвета из текстуры
            unsigned int color = texture_data[texHeight * texY + texX];
            if (side == 1)
            {
                color = (color >> 1) & 0x7F7F7F; // Затемнение для боковых стен
            }

            // Отрисовка вертикальной линии
            data->img_data[y * data->w + x] = color;
        }
    }
       // Движение вперёд
        if (keys->up)
        {
            double newX = data->posX + data->dirX * data->moveSpeed;
            double newY = data->posY + data->dirY * data->moveSpeed;

    // Проверка для движения вперед
            if (newX >= 0 && newX < 24 && (int)data->posY >= 0 && (int)data->posY < 24 && worldMap[(int)newX][(int)newY] == 0)
            {
                data->posX = newX;
            }
            if ((int)data->posX >= 0 && (int)data->posX < 24 && newY >= 0 && newY < 24 && worldMap[(int)newX][(int)newY] == 0)
            {
                data->posX = newX;
            }
        }

        if (keys->down)
        {
            double newX = data->posX - data->dirX * data->moveSpeed;
            double newY = data->posY - data->dirY * data->moveSpeed;

    // Проверка для движения назад
            if (newX >= 0 && newX < 24 && (int)data->posY >= 0 && (int)data->posY < 24 && worldMap[(int)newX][(int)newY] == 0)
            {
                data->posX = newX;
            }
            if ((int)data->posX >= 0 && (int)data->posX < 24 && newY >= 0 && newY < 24 && worldMap[(int)newX][(int)newY] == 0)
            {
                data->posX = newX;
            }
        }

        if (keys->right)
        {
    // Рассчитываем новые координаты, перемещая игрока вправо
            double newX = data->posX + data->dirY * data->moveSpeed;
            double newY = data->posY - data->dirX * data->moveSpeed;

    // Проверка для перемещения вправо
            if (newX >= 0 && newX < 24 && newY >= 0 && newY < 24 && worldMap[(int)newX][(int)newY] == 0)
            {
                data->posX = newX;
                data->posY = newY;
            }
        }

// Перемещение влево
        if (keys->left)
        {
    // Рассчитываем новые координаты, перемещая игрока влево
            double newX = data->posX - data->dirY * data->moveSpeed;
            double newY = data->posY + data->dirX * data->moveSpeed;

    // Проверка для перемещения влево
            if (newX >= 0 && newX < 24 && newY >= 0 && newY < 24 && worldMap[(int)newX][(int)newY] == 0)
            {
                data->posX = newX;
                data->posY = newY;
            }
        }
        

        if (keys->pov_left)
        {
            double oldDirX = data->dirX;

    // Поворот направления камеры
            data->dirX = data->dirX * COS_ROT - data->dirY * (-SIN_ROT);
            data->dirY = oldDirX * (-SIN_ROT) + data->dirY * COS_ROT;

    // Поворот плоскости экрана
            double oldPlaneX = data->planeX;
            data->planeX = data->planeX * COS_ROT - data->planeY * (-SIN_ROT);
            data->planeY = oldPlaneX * (-SIN_ROT) + data->planeY * COS_ROT;
        }

        if (keys->pov_right)
        {
            double oldDirX = data->dirX;

    // Поворот направления камеры
            data->dirX = data->dirX * COS_ROT - data->dirY * SIN_ROT;
            data->dirY = oldDirX * SIN_ROT + data->dirY * COS_ROT;

    // Поворот плоскости экрана
            double oldPlaneX = data->planeX;
            data->planeX = data->planeX * COS_ROT - data->planeY * SIN_ROT;
            data->planeY = oldPlaneX * SIN_ROT + data->planeY * COS_ROT;
        }

        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);

    // Шаг 6: Очистка ресурсов
        mlx_destroy_image(data->mlx_ptr, data->img);
    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    t_data *data;
    t_KeyState keys;

    keys.up = 0;
    keys.down = 0;
    keys.right = 0;
    keys.left = 0;
    keys.pov_left = 0;
    keys.pov_right = 0;

    data = malloc(sizeof(t_data));
    
    if(!data)
    {
        printf("Ошибка: не удалось выделить память\n");
        return (1);
    }
    
    // Инициализация MiniLibX
    void *mlx_ptr = mlx_init();
    if (!mlx_ptr)
    {
        printf("Ошибка: не удалось инициализировать MiniLibX\n");
        return 1;
    }

    // Создание окна
    void *win_ptr = mlx_new_window(mlx_ptr, screenWidth, screenHeight, "Raycaster");
    if (!win_ptr)
    {
        printf("Ошибка: не удалось создать окно\n");
        return 1;
    }

    printf("Raycaster screen: %dx%d\n", screenWidth, screenHeight);


    data->mlx_ptr = mlx_ptr;
    data->win_ptr = win_ptr;
    data->keys = &keys;
    data->posX = 22;
    data->posY = 11.5;
    data->dirX = -1;
    data->dirY = 0;
    data->planeX = 0;
    data->planeY = 0.66;
    data->w = screenWidth;
    data->h = screenHeight;
    data->moveSpeed = MOVE_SPEED;
    data->rotSpeed = ROT_SPEED;

    init_sprite_path(data);
	init_sprite(data);
    
    mlx_hook(win_ptr, 2, 1L << 0, key_hook, &keys);
    mlx_hook(win_ptr, 3, 1L << 1, key_release_hook, &keys);
    mlx_loop_hook(mlx_ptr, render, data);
    mlx_loop(mlx_ptr);
}

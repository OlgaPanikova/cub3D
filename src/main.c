/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:28:49 by lelichik          #+#    #+#             */
/*   Updated: 2024/09/26 16:50:43 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

int worldMap[24][29]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double absValue(double x)
{
    if (x < 0)
        return -x;
    else
        return x;
}
int key_hook(int keycode, void *param)
{
    t_KeyState *keys = (t_KeyState *)param;
    
    if (keycode == 53)
	{
        mlx_destroy_window(keys->data->mlx_ptr, keys->data->win_ptr); // Закрытие окна
        //ДОБАЧИТЬ ОЧИСТКУ ПАМЯТИ 
        exit(0); // Выход из программы
	}
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
    return (0);
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
    return (0);
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
    for (int i = 0; i < 4; ++i)
    {
        data->textures[i] = file_to_image(data, data->textures_path[i]);
    }
}

void init_sprite_path(t_data *data)
{
    data->textures_path[0] = "./NO.xpm"; // буду записывать из строки после парсинга 
    data->textures_path[1] = "./SO.xpm"; // буду записывать из строки после парсинга 
    data->textures_path[2] = "./WE.xpm"; // буду записывать из строки после парсинга 
    data->textures_path[3] = "./EA.xpm"; // буду записывать из строки после парсинга 
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

void calculate_ray_direction(t_data *data, int x)
{
    double cameraX;

    cameraX = 2 * x / (double)data->w - 1;
    data->ray.rayDirX = data->player.dirX + data->player.planeX * cameraX;
    data->ray.rayDirY = data->player.dirY + data->player.planeY * cameraX;
    data->ray.mapX = (int)data->player.posX;
    data->ray.mapY = (int)data->player.posY;

    data->ray.deltaDistY = absValue(1 / data->ray.rayDirY);
    data->ray.deltaDistX = absValue(1 / data->ray.rayDirX);
}

void calculate_initial_step(t_data *data)
{
    if (data->ray.rayDirX < 0)
    {
        data->ray.stepX = -1;
        data->ray.sideDistX = (data->player.posX - data->ray.mapX) * data->ray.deltaDistX;
    }
    else
    {
        data->ray.stepX = 1;
        data->ray.sideDistX = (data->ray.mapX + 1.0 - data->player.posX) * data->ray.deltaDistX;
    }

    if (data->ray.rayDirY < 0)
    {
        data->ray.stepY = -1;
        data->ray.sideDistY = (data->player.posY - data->ray.mapY) * data->ray.deltaDistY;
    }
    else
    {
        data->ray.stepY = 1;
        data->ray.sideDistY = (data->ray.mapY + 1.0 - data->player.posY) * data->ray.deltaDistY;
    }
}

int detect_wall_hit(t_data *data)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        if (data->ray.sideDistX < data->ray.sideDistY)
        {
            data->ray.sideDistX += data->ray.deltaDistX;
            data->ray.mapX += data->ray.stepX;
            data->ray.side = 0;
        }
        else
        {
            data->ray.sideDistY += data->ray.deltaDistY;
            data->ray.mapY += data->ray.stepY;
            data->ray.side = 1;
        }
        if (worldMap[data->ray.mapX][data->ray.mapY] > 0)
            hit = 1;
    }
    return hit;
}

double calculate_perpendicular_distance(t_data *data)
{
    if (data->ray.side == 0)
    {
        return (data->ray.mapX - data->player.posX + (1 - data->ray.stepX) / 2) / data->ray.rayDirX;
    }
    else
    {
        return (data->ray.mapY - data->player.posY + (1 - data->ray.stepY) / 2) / data->ray.rayDirY;
    }
}


void draw_wall(t_data *data, int x, int drawStart, int drawEnd, double wallX, int *texture_data, int lineHeight)
{
    int texX = (int)(wallX * texWidth);

    // Определяем текстуру и корректируем texX в зависимости от направления луча
    if (data->ray.side == 0)  // Столкновение с вертикальной стеной (восток или запад)
    {
        if (data->ray.rayDirX > 0) // Восточная стена (EA)
        {
            texX = texWidth - texX - 1;
            texture_data = (int *)mlx_get_data_addr(data->textures[0], &data->bpp, &data->size_line, &data->endian);
        }
        else if (data->ray.rayDirX < 0)
        {
            texture_data = (int *)mlx_get_data_addr(data->textures[2], &data->bpp, &data->size_line, &data->endian);
        }
    }
    else  // Столкновение с горизонтальной стеной (север или юг)
    {
        if (data->ray.rayDirY > 0) // Северная стена (NO)
        {
            texture_data = (int *)mlx_get_data_addr(data->textures[3], &data->bpp, &data->size_line, &data->endian);
        }
        else if (data->ray.rayDirY < 0)
        {
            texX = texWidth - texX - 1;
            texture_data = (int *)mlx_get_data_addr(data->textures[1], &data->bpp, &data->size_line, &data->endian);
        }
    }

    // Расчет шага по текстуре и начальной позиции
    double step = 1.0 * texHeight / lineHeight;
    double texPos = (drawStart - data->h / 2 + lineHeight / 2) * step;

    // Рисование стены
    for (int y = drawStart; y < drawEnd; y++)
    {
        int texY = (int)texPos % texHeight;
        texPos += step;

        unsigned int color = texture_data[texHeight * texY + texX];

        data->img_data[y * data->w + x] = color;
    }
}


int is_space_free(t_data *data)
{
    int newX = (int)data->player.newX;
    int newY = (int)data->player.newY;

    if (newX >= 0 && newX < data->w && newY >= 0 && newY < data->h)
    {
        return worldMap[newX][newY] == 0; // Убедись, что внутри карты и нет стены
    }
    return 0;
}

void move_forward(t_data *data)
{
    data->player.newX = data->player.posX + data->player.dirX * data->player.moveSpeed;
    data->player.newY = data->player.posY + data->player.dirY * data->player.moveSpeed;

    // Жесткая проверка на обе оси (X и Y)
    if (is_space_free(data))
    {
        // Проверяем, не слишком ли близко игрок к стене по оси X
        if (worldMap[(int)(data->player.newX + data->player.dirX * 0.1)][(int)data->player.posY] == 0)
        {
            data->player.posX = data->player.newX;
        }

        // Проверяем, не слишком ли близко игрок к стене по оси Y
        if (worldMap[(int)data->player.posX][(int)(data->player.newY + data->player.dirY * 0.1)] == 0)
        {
            data->player.posY = data->player.newY;
        }
    }
}
void move_backward(t_data *data)
{
    data->player.newX = data->player.posX - data->player.dirX * data->player.moveSpeed;
    data->player.newY = data->player.posY - data->player.dirY * data->player.moveSpeed;

    if (is_space_free(data))
    {
        if (worldMap[(int)(data->player.newX - data->player.dirX * 0.1)][(int)data->player.posY] == 0)
        {
            data->player.posX = data->player.newX;
        }

        if (worldMap[(int)data->player.posX][(int)(data->player.newY - data->player.dirY * 0.1)] == 0)
        {
            data->player.posY = data->player.newY;
        }
    }
}

void move_right(t_data *data)
{
    data->player.newX = data->player.posX + data->player.dirY * data->player.moveSpeed;
    data->player.newY = data->player.posY - data->player.dirX * data->player.moveSpeed;

    if (is_space_free(data))
    {
        // Проверяем коллизии для оси X с корректным использованием вектора бокового движения
        if (worldMap[(int)(data->player.newX + data->player.dirY * 0.1)][(int)data->player.posY] == 0)
        {
            data->player.posX = data->player.newX;
        }

        // Проверяем коллизии для оси Y с корректным использованием вектора бокового движения
        if (worldMap[(int)data->player.posX][(int)(data->player.newY - data->player.dirX * 0.1)] == 0)
        {
            data->player.posY = data->player.newY;
        }
    }
}
void move_left(t_data *data)
{
    data->player.newX = data->player.posX - data->player.dirY * data->player.moveSpeed;
    data->player.newY = data->player.posY + data->player.dirX * data->player.moveSpeed;

    if (is_space_free(data))
    {
        // Проверяем коллизии для оси X с корректным использованием вектора бокового движения
        if (worldMap[(int)(data->player.newX - data->player.dirY * 0.1)][(int)data->player.posY] == 0)
        {
            data->player.posX = data->player.newX;
        }

        // Проверяем коллизии для оси Y с корректным использованием вектора бокового движения
        if (worldMap[(int)data->player.posX][(int)(data->player.newY + data->player.dirX * 0.1)] == 0)
        {
            data->player.posY = data->player.newY;
        }
    }
}

void rotate_left(t_data *data)
{
    double oldDirX = data->player.dirX;
    data->player.dirX = data->player.dirX * COS_ROT - data->player.dirY * (-SIN_ROT);
    data->player.dirY = oldDirX * (-SIN_ROT) + data->player.dirY * COS_ROT;

    double oldPlaneX = data->player.planeX;
    data->player.planeX = data->player.planeX * COS_ROT - data->player.planeY * (-SIN_ROT);
    data->player.planeY = oldPlaneX * (-SIN_ROT) + data->player.planeY * COS_ROT;
}

void rotate_right(t_data *data)
{
    double oldDirX = data->player.dirX;
    data->player.dirX = data->player.dirX * COS_ROT - data->player.dirY * SIN_ROT;
    data->player.dirY = oldDirX * SIN_ROT + data->player.dirY * COS_ROT;

    double oldPlaneX = data->player.planeX;
    data->player.planeX = data->player.planeX * COS_ROT - data->player.planeY * SIN_ROT;
    data->player.planeY = oldPlaneX * SIN_ROT + data->player.planeY * COS_ROT;
}

int render(void *param)
{
    t_data *data = (t_data *)param;
    clear_image(data); // очистка экрана
    draw_floor_and_ceiling(data); // отрисовка пола и потолка

    for (int x = 0; x < data->w; x++)
    {
        calculate_ray_direction(data, x); // расчет направления луча 
        calculate_initial_step(data); // установка значений на карте до момента когда он встретится со стеной 
        detect_wall_hit(data); // поиск столкновения луча со стеной 

        double perpWallDist = calculate_perpendicular_distance(data); // расчет от игрока до стены для отрисовки высоты стен 

        int lineHeight = (int)(data->h / perpWallDist); // вычисление высоты стены чем ближе тем выше 
        int drawStart = -lineHeight / 2 + data->h / 2; // координата верхней части стены 
        int drawEnd = lineHeight / 2 + data->h / 2; // координата нижней части стены 

        if (drawStart < 0) // проверка границ экрана 
            drawStart = 0;
        if (drawEnd >= data->h)
            drawEnd = data->h - 1;

       double wallX;

        if (data->ray.side == 0)
            wallX = data->player.posY + perpWallDist * data->ray.rayDirY;

        else
            wallX = data->player.posX + perpWallDist * data->ray.rayDirX;

        wallX -= (int)wallX;
        
        int *texture_data = (int *)mlx_get_data_addr(data->textures[0], &data->bpp, &data->size_line, &data->endian);

        draw_wall(data, x, drawStart, drawEnd, wallX, texture_data, lineHeight);

    }
    if (data->keys->up)
        move_forward(data);
    if (data->keys->down)
        move_backward(data);
    if (data->keys->left)
        move_left(data);
    if (data->keys->right)
        move_right(data);
    if (data->keys->pov_left)
        rotate_left(data);
    if (data->keys->pov_right)
        rotate_right(data);

    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
    mlx_destroy_image(data->mlx_ptr, data->img);
    return 0;
}


int close_window(void *param)
{
    t_data *data = (t_data *)param;
    
    if (data->mlx_ptr && data->win_ptr)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        // ДОБАВИТЬ ОЧИСТКУ ПАМЯТИ
        exit(0);
    }
    return (0);
}



// int mouse_move(int x, t_data *data)
// {
//     static int prev_x = 0; // Сохраняем предыдущее положение по X для расчета смещения
//     int delta_x = x - prev_x;

//     prev_x = x; // Обновляем предыдущее положение

//     if (delta_x != 0)
//     {
//         // Рассчитываем угол поворота на основе delta_x (чем больше смещение, тем сильнее поворот)
//         double rotation_speed = 0.005; // Настроить скорость поворота для удобства
//         double rot_angle = delta_x * rotation_speed;

//         // Вращение камеры на основе угла поворота
//         double oldDirX = data->player.dirX;
//         data->player.dirX = data->player.dirX * cos(rot_angle) - data->player.dirY * sin(rot_angle);
//         data->player.dirY = oldDirX * sin(rot_angle) + data->player.dirY * cos(rot_angle);

//         double oldPlaneX = data->player.planeX;
//         data->player.planeX = data->player.planeX * cos(rot_angle) - data->player.planeY * sin(rot_angle);
//         data->player.planeY = oldPlaneX * sin(rot_angle) + data->player.planeY * cos(rot_angle);
//     }

//     return 0;
// }

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
    data->player.posX = 22.5;
    data->player.posY = 12;
    data->player.dirX = -1;
    data->player.dirY = 0;
    data->player.planeX = 0;
    data->player.planeY = 0.66;
    data->w = screenWidth;
    data->h = screenHeight;
    data->player.moveSpeed = MOVE_SPEED;
    data->player.rotSpeed = ROT_SPEED;
    keys.data = data;
    
    // добавить инициализацию стуктур и добавление памяти и зануление

    init_sprite_path(data);
	init_sprite(data);
    
    mlx_hook(win_ptr, 2, 1L << 0, key_hook, &keys);
    mlx_hook(win_ptr, 3, 1L << 1, key_release_hook, &keys);
    // mlx_hook(win_ptr, 6, 0, mouse_move, data);
    mlx_hook(win_ptr, 17, 0L, close_window, data);
    mlx_loop_hook(mlx_ptr, render, data);
    mlx_loop(mlx_ptr);
    // добавить очистку памяти 
}

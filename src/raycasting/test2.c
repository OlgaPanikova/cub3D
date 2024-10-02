#include "cub3D.h"
#include <math.h>
#include "cub3D.h"


void    char_spice(t_cub *data)
{
    int y = 0;
    int x;

    while(data->map[y] != NULL)
    {
        x = 0;
        while(data->map[y][x] != '\0')
        {
            if(data->map[y][x] == ' ')
                data->map[y][x] = '0';
            x++;
        }
        y++;
    }
}
int *strtoint(char *str) {
    int *int_arr;
    int i, j;

    int_arr = (int *)malloc((ft_strlen(str) + 1) * sizeof(int)); // Выделение памяти
    if (!int_arr)
        return NULL; // Проверка на успешное выделение памяти
    i = 0;
    j = 0;
    while (str[i] != '\0') {
        int_arr[j] = str[i] - '0';  // Преобразуем символ в число
        j++;  // Увеличиваем индекс для чисел
        i++;
    }
    int_arr[j] = -1;  // Устанавливаем конец массива (если нужно)
    return int_arr;
}

void convert_to_int(t_cub *data) {
    int y = 0;
    
    while (data->map[y])
        y++;  // Подсчет количества строк
    
    data->worldMap = (int **)malloc((y + 1) * sizeof(int *)); // Выделение памяти под указатели
    if (!data->worldMap)
        return; // Проверка на успешное выделение памяти
    
    data->worldMap[y] = NULL;  // Последний элемент NULL
    
    y = 0;
    while (data->map[y]) {
        data->worldMap[y] = strtoint(data->map[y]); // Конвертация строки в массив чисел
        y++;
    }
}

void	calculations_camera(t_cub *data, char direction)
{
	if (direction == 'N')
	{
		data->player.dirY = 0;
		data->player.dirX = -1;
		data->player.planeY = 0.66;
		data->player.planeX = 0;
	}
	else if (direction == 'S') // Смотрит на юг
	{
		data->player.dirY = 0;
		data->player.dirX = 1;
		data->player.planeY = -0.66;
		data->player.planeX = 0;
	}
	else if (direction == 'W') // Смотрит на запад
	{
		data->player.dirY = -1;
		data->player.dirX = 0;
		data->player.planeY = 0;
		data->player.planeX = -0.66;
	}
	else if (direction == 'E') // Смотрит на восток
	{
		data->player.dirY = 1;
		data->player.dirX = 0;
		data->player.planeY = 0;
		data->player.planeX = 0.66;
	}
}

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

void draw_floor_and_ceiling(t_cub *data)
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

void *file_to_image(t_cub *data, char *textures_path)
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

void init_sprite(t_cub *data)
{
    for (int i = 0; i < 4; ++i)
    {
        data->textures[i] = file_to_image(data, data->textures_path[i]);
    }
}

void init_sprite_path(t_cub *data)
{
    data->textures_path[0] = "./NO.xpm"; // буду записывать из строки после парсинга 
    data->textures_path[1] = "./SO.xpm"; // буду записывать из строки после парсинга 
    data->textures_path[2] = "./WE.xpm"; // буду записывать из строки после парсинга 
    data->textures_path[3] = "./EA.xpm"; // буду записывать из строки после парсинга 
}

void clear_image(t_cub *data)
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

void calculate_ray_direction(t_cub *data, int x)
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

void calculate_initial_step(t_cub *data)
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

int detect_wall_hit(t_cub *data)
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
        if (data->worldMap[data->ray.mapX][data->ray.mapY] == 1)
            hit = 1;
    }
    return hit;
}

double calculate_perpendicular_distance(t_cub *data)
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

void draw_wall(t_cub *data, int x, int drawStart, int drawEnd, double wallX, int *texture_data, int lineHeight)
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


int is_space_free(t_cub *data)
{
    int newX = (int)data->player.newX;
    int newY = (int)data->player.newY;

    if (newX >= 0 && newX < data->w && newY >= 0 && newY < data->h)
    {
        return data->worldMap[newX][newY] == 0; // Убедись, что внутри карты и нет стены
    }
    return 0;
}

void move_forward(t_cub *data)
{
    data->player.newX = data->player.posX + data->player.dirX * data->player.moveSpeed;
    data->player.newY = data->player.posY + data->player.dirY * data->player.moveSpeed;

    // Жесткая проверка на обе оси (X и Y)
    if (is_space_free(data))
    {
        // Проверяем, не слишком ли близко игрок к стене по оси X
        if (data->worldMap[(int)(data->player.newX + data->player.dirX * 0.1)][(int)data->player.posY] == 0)
        {
            data->player.posX = data->player.newX;
        }

        // Проверяем, не слишком ли близко игрок к стене по оси Y
        if (data->worldMap[(int)data->player.posX][(int)(data->player.newY + data->player.dirY * 0.1)] == 0)
        {
            data->player.posY = data->player.newY;
        }
    }
}
void move_backward(t_cub *data)
{
    data->player.newX = data->player.posX - data->player.dirX * data->player.moveSpeed;
    data->player.newY = data->player.posY - data->player.dirY * data->player.moveSpeed;

    if (is_space_free(data))
    {
        if (data->worldMap[(int)(data->player.newX - data->player.dirX * 0.1)][(int)data->player.posY] == 0)
        {
            data->player.posX = data->player.newX;
        }

        if (data->worldMap[(int)data->player.posX][(int)(data->player.newY - data->player.dirY * 0.1)] == 0)
        {
            data->player.posY = data->player.newY;
        }
    }
}

void move_right(t_cub *data)
{
    data->player.newX = data->player.posX + data->player.dirY * data->player.moveSpeed;
    data->player.newY = data->player.posY - data->player.dirX * data->player.moveSpeed;

    if (is_space_free(data))
    {
        // Проверяем коллизии для оси X с корректным использованием вектора бокового движения
        if (data->worldMap[(int)(data->player.newX + data->player.dirY * 0.1)][(int)data->player.posY] == 0)
        {
            data->player.posX = data->player.newX;
        }

        // Проверяем коллизии для оси Y с корректным использованием вектора бокового движения
        if (data->worldMap[(int)data->player.posX][(int)(data->player.newY - data->player.dirX * 0.1)] == 0)
        {
            data->player.posY = data->player.newY;
        }
    }
}
void move_left(t_cub *data)
{
    data->player.newX = data->player.posX - data->player.dirY * data->player.moveSpeed;
    data->player.newY = data->player.posY + data->player.dirX * data->player.moveSpeed;

    if (is_space_free(data))
    {
        // Проверяем коллизии для оси X с корректным использованием вектора бокового движения
        if (data->worldMap[(int)(data->player.newX - data->player.dirY * 0.1)][(int)data->player.posY] == 0)
        {
            data->player.posX = data->player.newX;
        }

        // Проверяем коллизии для оси Y с корректным использованием вектора бокового движения
        if (data->worldMap[(int)data->player.posX][(int)(data->player.newY + data->player.dirX * 0.1)] == 0)
        {
            data->player.posY = data->player.newY;
        }
    }
}

void rotate_left(t_cub *data)
{
    double oldDirX = data->player.dirX;
    data->player.dirX = data->player.dirX * COS_ROT - data->player.dirY * (-SIN_ROT);
    data->player.dirY = oldDirX * (-SIN_ROT) + data->player.dirY * COS_ROT;

    double oldPlaneX = data->player.planeX;
    data->player.planeX = data->player.planeX * COS_ROT - data->player.planeY * (-SIN_ROT);
    data->player.planeY = oldPlaneX * (-SIN_ROT) + data->player.planeY * COS_ROT;
}

void rotate_right(t_cub *data)
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
    t_cub *data = (t_cub *)param;
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
    t_cub *data = (t_cub *)param;
    
    if (data->mlx_ptr && data->win_ptr)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        // ДОБАВИТЬ ОЧИСТКУ ПАМЯТИ
        exit(0);
    }
    return (0);
}


void	start_raycast(t_cub *data)
{
	init_sprite_path(data);
	init_sprite(data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_hook, data->keys);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_release_hook, data->keys);
    // mlx_hook(win_ptr, 6, 0, mouse_move, data);
	mlx_hook(data->win_ptr, 17, 0L, close_window, data); // добавить очистку памяти 
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_loop(data->mlx_ptr);
}

#include "cub3D.h"


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
    t_cub *data = (t_cub *)param;
    
    if (keycode == 53)
	{
        mlx_destroy_window(data->mlx_ptr, data->win_ptr); // Закрытие окна
        //ДОБАЧИТЬ ОЧИСТКУ ПАМЯТИ 
        exit(0); // Выход из программы
	}
    if (keycode == 13)
        move_forward(data);
    else if (keycode == 1)
        move_backward(data);
    else if (keycode == 0)
        move_left(data);
    else if (keycode == 2)
        move_right(data);
    else if (keycode == 123)
        rotate_left(data);
    else if (keycode == 124)
        rotate_right(data);
    return (0);
}

void draw_ceiling(t_cub *data)
{
	int				half_height;
	int				y;
	int				x;

	half_height = data->hight_screen / 2;
	y = 0;
	while (y < half_height)
	{
		x = 0;
		while (x < data->wight_screen)
		{
			data->image->addr[y * data->wight_screen + x++] = data->hex_ceiling;
		}
		y++;
	}
}

void	draw_floor(t_cub *data)
{
	int				half_height;
	int				i;
	int				j;

	half_height = data->hight_screen / 2;
	i = half_height;
	while (i < data->hight_screen)
	{
		j = 0;
		while (j < data->wight_screen)
		{
			data->image->addr[i * data->wight_screen + j++] = data->hex_floor;
			j++;
		}
		i++;
	}
}
void	draw_floor_and_ceiling(t_cub *data)
{
	draw_ceiling(data);  // Отрисовка потолка
	draw_floor(data);      // Отрисовка пола
}


void	get_tex_addr(t_cub *data)
{
	data->s->addr = (int *)mlx_get_data_addr(data->s->img, &data->s->bpp, \
		&data->s->size_line, &data->s->endian);
	data->w->addr = (int *)mlx_get_data_addr(data->w->img, &data->w->bpp, \
		&data->w->size_line, &data->w->endian);
	data->n->addr = (int *)mlx_get_data_addr(data->n->img, &data->n->bpp, \
		&data->n->size_line, &data->n->endian);
	data->e->addr = (int *)mlx_get_data_addr(data->e->img, &data->e->bpp, \
		&data->e->size_line, &data->e->endian);
}

void	init_texture(t_cub *data)
{
	data->n = malloc(sizeof(t_texture));
	data->n->img = mlx_xpm_file_to_image(data->mlx_ptr, data->north_texture, \
		&data->n->width, &data->n->height);
	data->w = malloc(sizeof(t_texture));
	data->w->img = mlx_xpm_file_to_image(data->mlx_ptr, data->west_texture, \
		&data->w->width, &data->w->height);
	data->s = malloc(sizeof(t_texture));
	data->s->img = mlx_xpm_file_to_image(data->mlx_ptr, data->south_texture, \
		&data->s->width, &data->s->height);
	data->e = malloc(sizeof(t_texture));
	data->e->img = mlx_xpm_file_to_image(data->mlx_ptr, data->east_texture, \
		&data->e->width, &data->e->height);
	if (data->n->img == NULL || data->w->img == NULL || \
		data->s->img == NULL || data->e->img == NULL)
		printf("Ошибка в текстурах"); // добавить очистку памяти 
	get_tex_addr(data);
	return ;
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

void calculate_ray_direction(t_cub *data, int x)
{
    data->cameraX = 2 * x / (double)data->wight_screen - 1;
    data->ray.rayDirX = data->player.dirX + data->player.planeX * data->cameraX;
    data->ray.rayDirY = data->player.dirY + data->player.planeY * data->cameraX;
    data->ray.mapX = (int)data->player.posX;
    data->ray.mapY = (int)data->player.posY;
    if (data->ray.rayDirX == 0)
		data->ray.deltaDistX = 1e30;
	else
		data->ray.deltaDistX = absValue(1 / data->ray.rayDirX);
	if (data->ray.rayDirY == 0)
		data->ray.deltaDistY = 1e30;
    else
		data->ray.deltaDistY = absValue(1 / data->ray.rayDirY);
    data->hit = 0;
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

void detect_wall_hit(t_cub *data)
{

    while (data->hit == 0)
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

        // Исправлено обращение к карте
        if (data->map[data->ray.mapX][data->ray.mapY] == '1')
            data->hit = 1;
    }
}

void	calculating_parameters_rendering_wall(t_cub *data)
{
	if (data->ray.side == 0)
		data->ray.perpWallDist = (data->ray.sideDistX - data->ray.deltaDistX);
	else
		data->ray.perpWallDist = (data->ray.sideDistY - data->ray.deltaDistY);
	data->lineheight = (int)(data->hight_screen / data->ray.perpWallDist);
	data->drawstart = -data->lineheight / 2 + data->hight_screen / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineheight / 2 + data->hight_screen / 2;
	if (data->drawend >= data->hight_screen)
		data->drawend = data->hight_screen - 1;
	if (data->ray.side == 1)
		data->color = data->color / 2;
	if (data->ray.side == 0)
		data->ray.wallx = data->player.posY + data->ray.perpWallDist * data->ray.rayDirY;
	else
		data->ray.wallx = data->player.posX + data->ray.perpWallDist * data->ray.rayDirX;
	data->ray.wallx -= floor(data->ray.wallx);
}


void	side_of_the_wall(t_cub *data)
{
	if (data->ray.side == 0)
	{
		if (data->ray.rayDirX > 0)
			data->wallt = data->e;
		else
			data->wallt = data->w;
	}
	else
	{
		if (data->ray.rayDirY > 0)
			data->wallt = data->n;
		else
			data->wallt = data->s;
	}
}

void	draw_wall(t_cub *data, int x)
{
	int	y;

	data->texx = (int)(data->ray.wallx * (double)data->wallt->width);
	if ((data->ray.side == 0 && data->ray.rayDirX > 0) \
		|| (data->ray.side == 1 && data->ray.rayDirY < 0))
		data->texx = data->wallt->width - data->texx - 1;
	data->texheight = (int)(data->hight_screen / data->ray.perpWallDist);
	data->drawstart = -data->texheight / 2 + data->hight_screen / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->texheight / 2 + data->hight_screen / 2;
	if (data->drawend >= data->hight_screen)
		data->drawend = data->hight_screen - 1;
	y = data->drawstart;
	while (y < data->drawend)
	{
		data->texy = (int)(((y - data->hight_screen / 2 + data->texheight / 2) \
			* data->wallt->height) / data->texheight);
		data->color = data->wallt->addr[data->texy \
			* data->wallt->width + data->texx];
		data->image->addr[y * data->wight_screen + x] = data->color;
		y++;
	}
}

int is_space_free(t_cub *data)
{
    int newX = (int)data->player.newX; // X - ширина
    int newY = (int)data->player.newY; // Y - высота

    if (newY >= 0 && newY < data->map_height && newX >= 0 && newX < data->map_width) // Проверяем границы
    {
        return data->map[newY][newX] == '0'; // Проверяем, что это свободное поле
    }
    return 0;
}

void	move_forward(t_cub *data)
{
	if (data->map[(int)(data->player.posX + data->player.dirX * \
		data->player.moveSpeed)][(int)data->player.posY] != '1')
		data->player.posX += data->player.dirX * data->player.moveSpeed;
	if (data->map[(int)data->player.posX][(int)(data->player.posY + \
		data->player.dirY * data->player.moveSpeed)] != '1')
		data->player.posY += data->player.dirY * data->player.moveSpeed;
	start_raycast(data);
}

void	move_backward(t_cub *data)
{
	if (data->map[(int)(data->player.posX - data->player.dirX * \
		data->player.moveSpeed)][(int)data->player.posY] != '1')
		data->player.posX -= data->player.dirX * data->player.moveSpeed;
	if (data->map[(int)data->player.posX][(int)(data->player.posY - \
		data->player.dirY * data->player.moveSpeed)] != '1')
		data->player.posY -= data->player.dirY * data->player.moveSpeed;
	start_raycast(data);
}
void	move_right(t_cub *data)
{
	if (data->map[(int)(data->player.posX + data->player.dirY * \
		data->player.moveSpeed)][(int)data->player.posY] != '1')
		data->player.posX += data->player.dirY * data->player.moveSpeed;
	if (data->map[(int)data->player.posX][(int)(data->player.posY - \
		data->player.dirX * data->player.moveSpeed)] != '1')
		data->player.posY -= data->player.dirX * data->player.moveSpeed;
	start_raycast(data);
}

void	move_left(t_cub *data)
{
	if (data->map[(int)(data->player.posX - data->player.dirY * \
		data->player.moveSpeed)][(int)data->player.posY] != '1')
		data->player.posX -= data->player.dirY  * data->player.moveSpeed;
	if (data->map[(int)data->player.posX][(int)(data->player.posY + \
		data->player.dirX * data->player.moveSpeed)] != '1')
		data->player.posY += data->player.dirX * data->player.moveSpeed;
	start_raycast(data);
}

void	rotate_right(t_cub *data)
{
	data->olddirx = data->player.dirX;
	data->player.dirX = data->player.dirX * cos(-data->player.rotSpeed) - data->player.dirY * \
		sin(-data->player.rotSpeed);
	data->player.dirY = data->olddirx * sin(-data->player.rotSpeed) + data->player.dirY * \
		cos(-data->player.rotSpeed);
	data->oldplanex = data->player.planeX;
	data->player.planeX = data->player.planeX * cos(-data->player.rotSpeed) - data->player.planeY * \
		sin(-data->player.rotSpeed);
	data->player.planeY = data->oldplanex * sin(-data->player.rotSpeed) + data->player.planeY * \
		cos(-data->player.rotSpeed);
	start_raycast(data);
}

void	rotate_left(t_cub *data)
{
	data->olddirx = data->player.dirX;
	data->player.dirX = data->player.dirX * cos(data->player.rotSpeed) - data->player.dirY * \
		sin(data->player.rotSpeed);
	data->player.dirY = data->olddirx * sin(data->player.rotSpeed) + data->player.dirY * \
		cos(data->player.rotSpeed);
	data->oldplanex = data->player.planeX;
	data->player.planeX = data->player.planeX * cos(data->player.rotSpeed) - data->player.planeY * \
		sin(data->player.rotSpeed);
	data->player.planeY = data->oldplanex * sin(data->player.rotSpeed) + data->player.planeY * \
		cos(data->player.rotSpeed);
	start_raycast(data);
}

void render(t_cub *data)
{
    int x;

    x = 0;

    while (x < data->wight_screen)
    {
        calculate_ray_direction(data, x); // расчет направления луча 
        calculate_initial_step(data); // установка значений на карте до момента когда он встретится со стеной 
        detect_wall_hit(data); // поиск столкновения луча со стеной 
        calculating_parameters_rendering_wall(data);
        side_of_the_wall(data);

        draw_wall(data, x);
        x++;

    }
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
    data->image = malloc(sizeof(t_texture));
    data->image->img = mlx_new_image(data->mlx_ptr, data->wight_screen, data->hight_screen);
    data->image->addr = (int *)mlx_get_data_addr(data->image->img, &data->image->bpp, &data->image->size_line, &data->image->endian);
    draw_floor_and_ceiling(data);
    render(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img, 0, 0);
    mlx_destroy_image(data->mlx_ptr, data->image->img);
    free(data->image);

}
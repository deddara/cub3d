/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:22:20 by deddara           #+#    #+#             */
/*   Updated: 2020/08/13 22:15:10 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"
#include <stdarg.h>
#include <wchar.h>
# include <sys/types.h>

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


//************************************************
//ОТРИСОВКА ПОТОЛКА И ПОЛА

void paint_fc(t_map *map, t_data *img)
{
	int y_c = 0;
	int x_c = 0;
	while (y_c < map->y / 2)
	{
		x_c = 0;
		while (x_c < map->x)
		{
			my_mlx_pixel_put(img, x_c, y_c, 0x00007E);
			x_c++;
		}
		y_c++;
	}
	while(y_c < map->y)
	{
		x_c = 0;
		while (x_c < map->x)
		{
			my_mlx_pixel_put(img, x_c, y_c, 0x343A41);
			x_c++;
		}
		y_c++;
	}
}

//ОТРИСОВКА ПОТОЛКА И ПОЛА
//************************************************
// static int skipper(t_map *map, int x, int y)
// {
// 	if (map->map[y][x] == ' ' || map->map[y][x] == '0' || map->map[y][x] == '2' || 
// 		map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'W'
// 		|| map->map[y][x] == 'E')
// 		return (1);
// 	return (0);
// }

// static void draw_rect(int x, int y, t_map *map, t_data *img)
// {
// 	int rect_x;
// 	int rect_y;
// 	int i, j;

// 	i = 0;
// 	j = 0;
	
// 	rect_x = x * (map->x / map->x_count / 3);
// 	rect_y = y * (map->y / map->y_count / 3);
	
// 	while (i < (map->x / map->x_count / 3) - 1)
// 	{
// 		j = 0;
// 	 	while (j < (map->y / map->y_count / 3) - 1)
// 		{
// 			my_mlx_pixel_put(img, rect_x + i, rect_y + j, 0xFFFF41);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void draw_player(int x, int y, t_map *map, t_data *img)
// {
// 	int rect_x;
// 	int rect_y;
// 	int i, j;

// 	i = 0;
// 	j = 0;
	
// 	rect_x = x * (map->x / map->x_count / 3) + ((map->x / map->x_count / 3) / 2);
// 	rect_y = y * (map->y / map->y_count / 3) + ((map->y / map->y_count / 3) / 2);
	
// 	while (i < 5)
// 	{
// 		j = 0;
// 	 	while (j < 5)
// 		{
// 			my_mlx_pixel_put(img, rect_x + i, rect_y + j, 0xFF0000);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void paint_map(t_map *map, t_data *img)
// {
// 	int x = 0;
// 	int y = 0;

// 	while (map->map[y])
// 	{
// 		x = 0;
// 		while (map->map[y][x])
// 		{
// 			if (skipper(map, x, y))
// 			{
// 				x++;
// 				continue ;
// 			}
// 			draw_rect(x, y, map, img);
// 			x++;
// 		}
// 		y++;
// 	}
// }

static int _init(t_raycast *ray, t_map *map)
{
	int i;

	i = 0;
	if(!(ray->x_buffer = (int*)malloc(sizeof(int) * map->x)))
		return (0);
	ray->player_x = (double)map->x_player + 0.5;
	ray->player_y = (double)map->y_player + 0.5;
	ray->dlt_dist_x = 0;
	ray->dlt_dist_y = 0;
	ray->time_curr = clock();
	ray->time_prev = 0;
	sprites_count(ray, map);
	dir_calc(ray, map);
	return (1);
}

static void keys_init (t_raycast *ray)
{
	ray->keys.w = 0;
	ray->keys.s = 0;
	ray->keys.a = 0;
	ray->keys.d = 0;
	ray->keys.l_arr = 0;
	ray->keys.r_arr = 0;
	ray->keys.esc = 0;
}

int             main(void)
{
	// paint_map(&map, &img);
	// draw_player(map.x_player, map.y_player, &map, &img);
    t_data  img;
    t_vars vars;
    t_map map;
	t_raycast ray;
	parser(&map); //парсинг карты
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, map.x, map.y, "Hello world!");
    img.img = mlx_new_image(vars.mlx, map.x, map.y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);	
	
	paint_fc(&map, &img);
	if(!_init(&ray, &map))
		return (0);
	ray.map = &map;
	ray.img = &img;
	ray.vars = &vars;
	keys_init(&ray);
	ray_caster(&map, &img, &ray);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0); 
	mlx_hook(vars.win, 2, 1L << 0, key_press, &ray);
	mlx_hook(vars.win, 3, 1L << 1, key_release, &ray);
	mlx_loop_hook(vars.mlx, key_controls, &ray);
    mlx_loop(vars.mlx);
	return (0);
}
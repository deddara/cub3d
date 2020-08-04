/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:22:20 by deddara           #+#    #+#             */
/*   Updated: 2020/08/02 19:54:30 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


//************************************************
//ОТРИСОВКА ПОТОЛКА И ПОЛА

static void paint_fc(t_map *map, t_data *img)
{
	int y_c = 0;
	int x_c = 0;
	while (y_c < map->y / 2)
	{
		x_c = 0;
		while (x_c < map->x)
		{
			my_mlx_pixel_put(img, x_c, y_c, 0x0000F9);
			x_c++;
		}
		y_c++;
	}
	while(y_c < map->y)
	{
		x_c = 0;
		while (x_c < map->x)
		{
			my_mlx_pixel_put(img, x_c, y_c, 0xFFFF41);
			x_c++;
		}
		y_c++;
	}
}

//ОТРИСОВКА ПОТОЛКА И ПОЛА
//************************************************

// static void paint_map(t_map *map, t_data *img)
// {
// 	int x;
// 	int y;
// 	int draw_x;
// 	int draw_y;
// 	int draw_xt;
// 	int draw_yt = 0;

// 	draw_x = -1;
// 	draw_y = 0;
// 	y = 0;
// 	while (map->map[y])
// 	{
// 		x = 0;
// 		draw_x = -1;
// 		while(map->map[y][x])
// 		{
// 			if (map->map[y][x] == '1')
// 			{	
// 				draw_yt = draw_y;
// 				draw_x = (draw_x == -1) ? x - 1 : draw_x;
// 				draw_xt = draw_x;
// 				while (draw_y < draw_yt + 20)
// 				{
// 					draw_x = draw_xt;
// 					while (draw_x < draw_xt + 20)
// 					{
// 						my_mlx_pixel_put(img, draw_x, draw_y, 0xFFFF41);
// 						draw_x++;
// 					}
// 					draw_y++;
// 				}
// 				draw_x++;
// 				draw_y = draw_yt;
// 			}
// 			else if (map->map[y][x] == '0' || map->map[y][x] == '2' || map->map[y][x] == 'S' || map->map[y][x] == ' ')
// 			{
// 				draw_x += 21;
// 			}
// 			x++;
// 		}
// 		draw_y = draw_yt + 21;
// 		y++;
// 	}
// }

// static void paint_player(t_map *map, t_data *img)
// {
// 	int c = 0;

// 	int x, y;

// 	x = 0;
// 	y = 0;
// 	map->x_player *= 21;
// 	map->y_player *= 21;

// 	while (c < 2000)
// 	{
// 		x = map->x_player + c * cos(map->a_player);
// 		y = map->y_player + c * sin(map->a_player);
// 		my_mlx_pixel_put(img, x, y, 0xFFFFFF);
// 		if (map->map[y / 21][x / 21] != '0' && map->map[y / 21][x / 21] != '2' && map->map[y / 21][x / 21] != 'N')
// 			break ;
// 		c++;
// 	}
// }

static int skipper(t_map *map, int x, int y)
{
	if (map[x][y] == ' ' || map[x][y] == '0' || map[x][y] == '2' || 
		map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'W'
		|| map[x][y] == 'E')
		return (1);
	return (0);
}

static void paint_map(t_map *map, t_data *img)
{
	int x = 0;
	int y = 0;

	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (skipper(map, x, y))
				continue ;
		}
	}
}

int             main(void)
{
    t_data  img;
    t_vars vars;
    t_map map;
    // int x;
    // int y;
	parser(&map); //парсинг карты
    // x = 5;
    // y = 5;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, map.x, map.y, "Hello world!");
    img.img = mlx_new_image(vars.mlx, map.x, map.y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	
	//paint_fc(&map, &img);
	paint_map(&map, &img);
	//paint_player(&map, &img);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0); 
    mlx_loop(vars.mlx);
	return (0);
}
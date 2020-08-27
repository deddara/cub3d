/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:35:57 by deddara           #+#    #+#             */
/*   Updated: 2020/08/27 18:05:02 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "main.h"

int		draw_health(t_raycast *ray)
{
	int y;
	int x;
	int pixel;
	
	y = 0;
	while (y < ray->map->y / 7)
	{	
		x = 0;
		while (x < ray->map->x / 5)
		{
			pixel = getpixelcolor(&ray->health, (int)((double)((x / (double)(ray->map->x / 5)) * ray->health.width)),\
			(int)((double)((y / (double)(ray->map->y / 7)) * ray->health.height)));
			if ((pixel & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(ray->img, ray->map->x - x, y, pixel);
			x++;
		}
		y++;
	}
	return (1);
}

static int skipper2(t_map *map, int x, int y)
{
	if (map->map[y][x] == ' ' || map->map[y][x] == '0' || map->map[y][x] == '2' || 
		map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'W'
		|| map->map[y][x] == 'E')
		return (1);
	return (0);
}

static void draw_rect(int x, int y, t_map *map, t_data *img)
{
	int rect_x;
	int rect_y;
	int i, j;

	i = 0;
	j = 0;
	
	rect_x = x * (map->x / map->x_count / 3);
	rect_y = y * (map->y / map->y_count / 3);
	
	while (i < (map->x / map->x_count / 3) - 1)
	{
		j = 0;
	 	while (j < (map->y / map->y_count / 3) - 1)
		{
			my_mlx_pixel_put(img, rect_x + i, rect_y + j, 0xFFFF41);
			j++;
		}
		i++;
	}
}

static void draw_player(double x, double y, t_map *map, t_data *img)
{
	double rect_x;
	double rect_y;
	int i, j;

	i = 0;
	j = 0;
	
	rect_x = (x - 0.6) * (map->x / map->x_count / 3) + ((map->x / map->x_count / 3) / 2);
	rect_y = (y - 0.6) * (map->y / map->y_count / 3) + ((map->y / map->y_count / 3) / 2);
	
	while (i < 5)
	{
		j = 0;
	 	while (j < 5)
		{
			my_mlx_pixel_put(img, rect_x + i, rect_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void paint_mini_map(t_raycast *ray)
{
	int x = 0;
	int y = 0;

	while (ray->map->map[y])
	{
		x = 0;
		while (ray->map->map[y][x])
		{
			if (skipper2(ray->map, x, y))
			{
				x++;
				continue ;
			}
			draw_rect(x, y, ray->map, ray->img);
			x++;
		}
		y++;
	}
	draw_player(ray->player_x, ray->player_y, ray->map, ray->img);
}
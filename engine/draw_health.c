/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:35:57 by deddara           #+#    #+#             */
/*   Updated: 2020/08/29 18:37:15 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "main.h"

int			draw_health(t_raycast *ray)
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
			pixel = getpixelcolor(&ray->health, (int)((double)\
			((x / (double)(ray->map->x / 5)) * ray->health.width)), (int)\
			((double)((y / (double)(ray->map->y / 7)) * ray->health.height)));
			if ((pixel & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(ray->img, ray->map->x - x, y, pixel);
			x++;
		}
		y++;
	}
	paint_mini_map(ray);
	return (1);
}

static void	draw_rect(int x, int y, t_map *map, t_data *img)
{
	int	rect_x;
	int	rect_y;
	int	i;
	int	j;

	i = 0;
	j = 0;
	rect_x = x * (map->x / map->x_count / 3);
	rect_y = y * (map->y / map->y_count / 3);
	while (i < (map->x / map->x_count / 3) - 1)
	{
		j = 0;
		while (j < (map->y / map->y_count / 3) - 1)
		{
			my_mlx_pixel_put(img, rect_x + i, rect_y + j, 0x01D4F8);
			j++;
		}
		i++;
	}
}

static void	draw_dir(t_raycast *ray, double rect_x, double rect_y)
{
	int k;

	k = 0;
	rect_x += 2;
	rect_y += 2;
	while (k < 10)
	{
		my_mlx_pixel_put(ray->img, rect_x, rect_y, 0xFF0000);
		rect_x += ray->ray_dir_x;
		rect_y += ray->ray_dir_y;
		k++;
	}
}

static void	draw_player(t_raycast *ray)
{
	double	rect_x;
	double	rect_y;
	int		i;
	int		j;

	i = 0;
	rect_x = (ray->player_x - 0.6) * (ray->map->x / ray->map->x_count / 3) \
	+ ((ray->map->x / ray->map->x_count / 3) / 2);
	rect_y = (ray->player_y - 0.6) * (ray->map->y / ray->map->y_count / 3) \
	+ ((ray->map->y / ray->map->y_count / 3) / 2);
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(ray->img, rect_x + i, rect_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
	draw_dir(ray, rect_x, rect_y);
}

void		paint_mini_map(t_raycast *ray)
{
	int x;
	int y;

	y = 0;
	while (ray->map->map[y])
	{
		x = 0;
		while (ray->map->map[y][x])
		{
			if (skipper(ray->map, y, x))
			{
				x++;
				continue ;
			}
			draw_rect(x, y, ray->map, ray->img);
			x++;
		}
		y++;
	}
	draw_player(ray);
}

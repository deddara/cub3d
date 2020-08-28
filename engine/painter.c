/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 18:02:29 by deddara           #+#    #+#             */
/*   Updated: 2020/08/28 16:11:07 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

static void	texture_clalcs(t_raycast *ray, t_paint *paint, t_map *map)
{
	ray->wall_height = (int)(map->y / ray->wall_dist);
	ray->wall_start = !ray->keys.ctrl ? (map->y / 2 - ray->wall_height / 2) : \
	(map->y / 3 - ray->wall_height / 2);
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = !ray->keys.ctrl ? (ray->wall_height / 2 + map->y / 2) : \
	(ray->wall_height / 2 + map->y / 3);
	if (ray->wall_end >= map->y)
		ray->wall_end = map->y - 1;
	if ((ray->wall_side == 2 || ray->wall_side == 3))
		paint->wall_x = ray->player_y + ray->wall_dist * ray->ray_dir_y;
	else
		paint->wall_x = ray->player_x + ray->wall_dist * ray->ray_dir_x;
	paint->wall_x -= floor((paint->wall_x));
	paint->tex_x = (int)(paint->wall_x * (double)(paint->tex_w));
	if (ray->wall_side == 2 || ray->wall_side == 1)
		paint->tex_x = paint->tex_w - paint->tex_x - 1;
	paint->step = 1.0 * paint->tex_h / ray->wall_height;
	paint->tex_pos = !ray->keys.ctrl ? (ray->wall_start - map->y / 2 \
	+ ray->wall_height / 2) * paint->step : \
	(ray->wall_start - map->y / 3 + ray->wall_height / 2) * paint->step;
}

static void	h_w_calcs(t_raycast *ray, t_paint *paint)
{
	if (ray->wall_side == 0)
	{
		paint->tex_w = ray->txtr_so.width;
		paint->tex_h = ray->txtr_so.height;
	}
	else if (ray->wall_side == 1)
	{
		paint->tex_w = ray->txtr_no.width;
		paint->tex_h = ray->txtr_no.height;
	}
	else if (ray->wall_side == 2)
	{
		paint->tex_w = ray->txtr_ea.width;
		paint->tex_h = ray->txtr_ea.height;
	}
	else if (ray->wall_side == 3)
	{
		paint->tex_w = ray->txtr_we.width;
		paint->tex_h = ray->txtr_we.height;
	}
}

void		paint_map(t_raycast *ray, t_map *map, t_data *img, int x)
{
	int		color;
	int		y;
	double	shade;
	t_paint	paint;

	h_w_calcs(ray, &paint);
	texture_clalcs(ray, &paint, map);
	y = ray->wall_start;
	shade = 1 / (1 + 0.005 * ray->wall_dist + 0.006 * \
			pow(ray->wall_dist, 2));
	while (y < ray->wall_end)
	{
		paint.tex_y = (int)paint.tex_pos & (paint.tex_h - 1);
		if (ray->wall_side == 0)
			color = getpixelcolor(&ray->txtr_so, paint.tex_x, paint.tex_y);
		else if (ray->wall_side == 1)
			color = getpixelcolor(&ray->txtr_no, paint.tex_x, paint.tex_y);
		else if (ray->wall_side == 2)
			color = getpixelcolor(&ray->txtr_ea, paint.tex_x, paint.tex_y);
		else if (ray->wall_side == 3)
			color = getpixelcolor(&ray->txtr_we, paint.tex_x, paint.tex_y);
		paint.tex_pos += paint.step;
		my_mlx_pixel_put(img, x, y, f_add_shade(color, shade));
		y++;
	}
}

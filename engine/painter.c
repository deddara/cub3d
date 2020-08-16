/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 18:02:29 by deddara           #+#    #+#             */
/*   Updated: 2020/08/16 18:19:29 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

void paint_map(t_raycast *ray, t_map *map, t_data *img, int x)
{
	int color;
	int y;

	color = 0;
	ray->wall_height = (int)(map->y / ray->wall_dist);
	ray->wall_start = (map->y / 2 - ray->wall_height / 2);
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = (ray->wall_height / 2 + map->y / 2);
	if (ray->wall_end >= map->y)
		ray->wall_end = map->y - 1;
	y = ray->wall_start;
	double wall_x;
	if ((ray->wall_side == 2 || ray->wall_side == 3))
		wall_x = ray->player_y + ray->wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->player_x + ray->wall_dist * ray->ray_dir_x;
	wall_x -= floor((wall_x));
	int tex_x = (int)(wall_x * (double)(ray->txtr_so.width));
	if (ray->wall_side == 2 || ray->wall_side == 1)
		tex_x = ray->txtr_so.width - tex_x - 1;
	double step = 1.0 * ray->txtr_so.height / ray->wall_height;
	double tex_pos = (ray->wall_start - map->y / 2 + ray->wall_height / 2) * step;
	while (y < ray->wall_end)
	{

		int tex_y = (int)tex_pos & (ray->txtr_so.height - 1);
		if (ray->wall_side == 0)
			color = getpixelcolor(&ray->txtr_so, tex_x, tex_y);
		else if (ray->wall_side == 1)
			color = getpixelcolor(&ray->txtr_no, tex_x, tex_y);
		else if (ray->wall_side == 2)
			color = getpixelcolor(&ray->txtr_ea, tex_x, tex_y);
		else if (ray->wall_side == 3)
			color = getpixelcolor(&ray->txtr_we, tex_x, tex_y);
		tex_pos += step;
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
}
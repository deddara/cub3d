/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 14:46:39 by deddara           #+#    #+#             */
/*   Updated: 2020/08/16 19:20:49 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "main.h"
# include <stdarg.h>
# include <wchar.h>
# include <sys/types.h>


void dir_calc(t_raycast *ray, t_map *map)
{
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
	if (map->player_pos == 'N')
	{
		ray->dir_y = -1;
		ray->plane_x = tan(M_PI * ANGLE / 360);
	}
	else if (map->player_pos == 'S')
	{
		ray->dir_y = 1;
		ray->plane_x = -tan(M_PI * ANGLE / 360);
	}
	else if (map->player_pos == 'W')
	{
		ray->dir_x = -1;
		ray->plane_y = -tan(M_PI * ANGLE / 360);
	}
	else if (map->player_pos == 'E')
	{
		ray->dir_x = 1;
		ray->plane_y = tan(M_PI * ANGLE / 360);
	}
}


static void step_side_calc(t_raycast *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->dist_x = (ray->player_x - ray->map_x) * ray->dlt_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = (1.0 + ray->map_x - ray->player_x ) * ray->dlt_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (ray->player_y - ray->map_y) * ray->dlt_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = (1.0 + ray->map_y - ray->player_y ) * ray->dlt_dist_y;
	}
}

static void check_wall(t_raycast *ray, t_map *map)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->dlt_dist_x;
			ray->map_x += ray->step_x;
			ray->wall_side = (ray->ray_dir_x < 0) ? 2 : 3;
		}
		else
		{
			ray->dist_y += ray->dlt_dist_y;
			ray->map_y += ray->step_y;
			ray->wall_side = (ray->ray_dir_y < 0) ? 0 : 1;
		}
		if (!skipper(map, ray->map_y, ray->map_x))
			ray->hit = 1;
	}
	if (ray->wall_side > 1)
		ray->wall_dist = ((ray->map_x - ray->player_x + (1 - ray->step_x) \
				/ 2) / ray->ray_dir_x);
	else
		ray->wall_dist = ((ray->map_y - ray->player_y + (1 - ray->step_y) \
				/ 2) / ray->ray_dir_y);
}

static void take_textures(t_raycast *ray)
{
	ray->txtr_so.img = mlx_xpm_file_to_image(ray->vars->mlx, ray->map->so, &ray->txtr_so.width, &ray->txtr_so.height);
	ray->txtr_so.addr = mlx_get_data_addr(ray->txtr_so.img, &ray->txtr_so.bits_per_pixel, \
					&ray->txtr_so.line_length, &ray->txtr_so.endian);
	ray->txtr_no.img = mlx_xpm_file_to_image(ray->vars->mlx, ray->map->no, &ray->txtr_no.width, &ray->txtr_no.height);
	ray->txtr_no.addr = mlx_get_data_addr(ray->txtr_no.img, &ray->txtr_no.bits_per_pixel, \
					&ray->txtr_no.line_length, &ray->txtr_no.endian);
	ray->txtr_ea.img = mlx_xpm_file_to_image(ray->vars->mlx, ray->map->ea, &ray->txtr_ea.width, &ray->txtr_ea.height);
	ray->txtr_ea.addr = mlx_get_data_addr(ray->txtr_ea.img, &ray->txtr_ea.bits_per_pixel, \
					&ray->txtr_ea.line_length, &ray->txtr_ea.endian);
	ray->txtr_we.img = mlx_xpm_file_to_image(ray->vars->mlx, ray->map->we, &ray->txtr_we.width, &ray->txtr_we.height);
	ray->txtr_we.addr = mlx_get_data_addr(ray->txtr_we.img, &ray->txtr_we.bits_per_pixel, \
					&ray->txtr_we.line_length, &ray->txtr_we.endian);
	ray->txtr_s.img = mlx_xpm_file_to_image(ray->vars->mlx, ray->map->s, &ray->txtr_s.width, &ray->txtr_s.height);
	ray->txtr_s.addr = mlx_get_data_addr(ray->txtr_s.img, &ray->txtr_s.bits_per_pixel, \
					&ray->txtr_s.line_length, &ray->txtr_s.endian);
}

void ray_caster(t_map *map, t_data *img, t_raycast *ray)
{
	int			x;
	x = 0;
	take_textures(ray);
	while (x < map->x)
	{
		ray->camera_x = 2 * x / (double)map->x - 1;
		ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		if (!ray->ray_dir_y)
			ray->dlt_dist_x = 0;
		else
			ray->dlt_dist_x = (!ray->ray_dir_x) ? 1 : fabs(1 / ray->ray_dir_x);
		if (!ray->ray_dir_x)
			ray->dlt_dist_y = 0;
		else
			ray->dlt_dist_y = (!ray->ray_dir_y) ? 1 : fabs(1 / ray->ray_dir_y);
		ray->map_x = (int)ray->player_x;
		ray->map_y = (int)ray->player_y;
		step_side_calc(ray);
		check_wall(ray, map);
		paint_map(ray, map, img, x);
		ray->x_buffer[x] = ray->wall_dist;
		x++;
	}
	sprite_handler(ray);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 14:46:39 by deddara           #+#    #+#             */
/*   Updated: 2020/08/09 17:01:14 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "main.h"

static void dir_calc(t_raycast *ray, t_map *map)
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

static void _init(t_raycast *ray, t_map *map)
{
	ray->player_x = (double)map->x_player + 0.5;
	ray->player_y = (double)map->y_player + 0.5;
	ray->dlt_dist_x = 0;
	ray->dlt_dist_y = 0;
	// ray->map_x = map->x_player;
	// ray->map_y = map->y_player;
	dir_calc(ray, map);
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
		ray->dist_x = (ray->player_x - ray->map_x) * ray->dlt_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (ray->player_y - ray->map_y) * ray->dlt_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = (ray->player_y - ray->map_y) * ray->dlt_dist_y;
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
		if (map->map[ray->map_y][ray->map_x] != '0')
			ray->hit = 1;
	}
	if (ray->wall_side > 1)
		ray->wall_dist = (double)(ray->map_x - ray->player_x + (1 - ray->step_x) \
				/ 2) / ray->ray_dir_x;
	else
		ray->wall_dist = (double)(ray->map_y - ray->player_y + (1 - ray->step_y) \
				/ 2) / ray->ray_dir_y;
}

static void paint_map(t_raycast *ray, t_map *map, t_data *img, int x)
{
	int color;

	ray->wall_height = (int)(map->y / ray->wall_dist);
	ray->wall_start =  -ray->wall_height / 2 + map->y / 2;
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->wall_height / 2 + map->y / 2;
	if (ray->wall_end >= map->y)
		ray->wall_end = map->y - 1;
	while (ray->wall_start <= ray->wall_end)
	{
		if (ray->wall_side == 0)
			color = 0x224A7B;
		else if (ray->wall_side == 1)
			color = 0xFF6524;
		else if (ray->wall_side == 2)
			color = 0xA7F192;
		else
			color = 0x888945;
		my_mlx_pixel_put(img, x, ray->wall_start, color);
		ray->wall_start++;
	}
}

void ray_caster(t_map *map, t_data *img)
{
	int			x;
	t_raycast	ray;

	_init(&ray, map);
	x = 0;
	while (x < map->x)
	{
		ray.camera_x = 2 * x / (double)map->x - 1;
		ray.ray_dir_x = ray.dir_x + ray.plane_x * ray.camera_x;
		ray.ray_dir_y = ray.dir_y + ray.plane_y * ray.camera_x;
		if (!ray.ray_dir_y)
			ray.dlt_dist_x = 0;
		else
			ray.dlt_dist_x = (!ray.ray_dir_x) ? 1 : fabs(1 / ray.ray_dir_x);
		if (!ray.ray_dir_x)
			ray.dlt_dist_y = 0;
		else
			ray.dlt_dist_y = (!ray.ray_dir_y) ? 1 : fabs(1 / ray.ray_dir_y);
		ray.map_x = map->x_player;
		ray.map_y = map->y_player;
		step_side_calc(&ray);
		check_wall(&ray, map);
		paint_map(&ray, map, img, x);
		x++;
	}
}
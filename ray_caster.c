/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 14:46:39 by deddara           #+#    #+#             */
/*   Updated: 2020/08/09 15:14:33 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
# include "engine.h"

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
	dir_calc(ray, map);
}

void ray_caster(t_map *map, t_data *img)
{
	int			x;
	t_raycast	ray;

	_init(&ray, map);
	x = 0;
	while (x < map->x)
	{

	}
}
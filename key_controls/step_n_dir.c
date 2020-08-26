/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_n_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:06:30 by deddara           #+#    #+#             */
/*   Updated: 2020/08/26 22:28:43 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

static int	skipper_move(t_map *map, int y, int x)
{
	if (map->map[y][x] == ' ' || map->map[y][x] == '0'
	|| map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'W'
		|| map->map[y][x] == 'E')
		return (1);
	return (0);
}

void		w_and_s_handler(t_raycast *ray)
{
	if (ray->keys.w)
	{
		if (skipper_move(ray->map, (int)ray->player_y,\
		(int)(ray->player_x + ray->dir_x * 0.21)))
			ray->player_x += ray->dir_x * 0.2;
		if (skipper_move(ray->map, (int)(ray->player_y + ray->dir_y * 0.21),\
		(int)ray->player_x))
			ray->player_y += ray->dir_y * 0.2;
	}
	if (ray->keys.s)
	{
		if (skipper_move(ray->map, (int)ray->player_y,\
		(int)(ray->player_x - ray->dir_x * 0.21)))
			ray->player_x -= ray->dir_x * 0.2;
		if (skipper_move(ray->map, (int)(ray->player_y - ray->dir_y * 0.21),\
		(int)ray->player_x))
			ray->player_y -= ray->dir_y * 0.2;
	}
}

void		d_and_a_handler(t_raycast *ray)
{
	if (ray->keys.a)
	{
		if (skipper_move(ray->map, (int)ray->player_y,\
		(int)(ray->player_x - ray->plane_x * 0.21)))
			ray->player_x -= ray->plane_x * 0.2;
		if (skipper_move(ray->map, (int)(ray->player_y - ray->plane_y * 0.21),\
		(int)ray->player_x))
			ray->player_y -= ray->plane_y * 0.2;
	}
	if (ray->keys.d)
	{
		if (skipper_move(ray->map, (int)ray->player_y,\
		(int)(ray->player_x + ray->plane_x * 0.21)))
			ray->player_x += ray->plane_x * 0.2;
		if (skipper_move(ray->map, (int)(ray->player_y + ray->plane_y * 0.21),\
		(int)ray->player_x))
			ray->player_y += ray->plane_y * 0.2;
	}
}

void		r_and_l_handler(t_raycast *ray)
{
	if (ray->keys.l_arr)
		l_arr_move(ray);
	if (ray->keys.r_arr)
		r_arr_move(ray);
}

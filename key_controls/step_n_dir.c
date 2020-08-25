/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_n_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:06:30 by deddara           #+#    #+#             */
/*   Updated: 2020/08/21 17:52:49 by deddara          ###   ########.fr       */
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
	double old_dir_x;
	double old_plane_x;

	if (ray->keys.l_arr)
	{
		old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-0.05) - ray->dir_y * sin(-0.05);
		ray->dir_y = old_dir_x * sin(-0.05) + ray->dir_y * cos(-0.05);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-0.05) - ray->plane_y * sin(-0.05);
		ray->plane_y = old_plane_x * sin(-0.05) + ray->plane_y * cos(-0.05);
	}
	if (ray->keys.r_arr)
	{
		old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(0.05) - ray->dir_y * sin(0.05);
		ray->dir_y = old_dir_x * sin(0.05) + ray->dir_y * cos(0.05);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(0.05) - ray->plane_y * sin(0.05);
		ray->plane_y = old_plane_x * sin(0.05) + ray->plane_y * cos(0.05);
	}
}

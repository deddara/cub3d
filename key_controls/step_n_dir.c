/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_n_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:06:30 by deddara           #+#    #+#             */
/*   Updated: 2020/08/18 18:07:37 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

void w_and_s_handler(t_raycast *ray)
{
	if (ray->keys.w) //w
	{
		if (skipper(ray->map, (int)ray->player_y, (int)(ray->player_x + ray->dir_x * 0.11)))
			ray->player_x +=  ray->dir_x * 0.1;
		if (skipper(ray->map, (int)(ray->player_y + ray->dir_y * 0.11), (int)ray->player_x ))
			ray->player_y +=  ray->dir_y * 0.1;
	}
	if (ray->keys.s) //s
	{
		if (skipper(ray->map, (int)ray->player_y, (int)(ray->player_x - ray->dir_x * 0.11)))
			ray->player_x -=  ray->dir_x * 0.1;
		if (skipper(ray->map, (int)(ray->player_y - ray->dir_y * 0.11), (int)ray->player_x ))
			ray->player_y -=  ray->dir_y * 0.1;
	}
}

void	d_and_a_handler(t_raycast *ray)
{
	if (ray->keys.a)//a
	{
		if (skipper(ray->map, (int)ray->player_y, (int)(ray->player_x - ray->plane_x * 0.11)))
			ray->player_x -=  ray->plane_x * 0.1;
		if (skipper(ray->map, (int)(ray->player_y - ray->plane_y * 0.11), (int)ray->player_x ))
			ray->player_y -=  ray->plane_y * 0.1;
	}
	if (ray->keys.d)//d
	{
		if (skipper(ray->map, (int)ray->player_y, (int)(ray->player_x + ray->plane_x * 0.11)))
			ray->player_x +=  ray->plane_x * 0.1;
		if (skipper(ray->map, (int)(ray->player_y + ray->plane_y * 0.11), (int)ray->player_x ))
			ray->player_y +=  ray->plane_y * 0.1;
	}
}

void	r_and_l_handler(t_raycast *ray)
{
	if (ray->keys.l_arr)
	{	
		double old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-0.05) - ray->dir_y * sin(-0.05);
		ray->dir_y = old_dir_x * sin(-0.05) + ray->dir_y * cos(-0.05);
		double old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-0.05) - ray->plane_y * sin(-0.05);
		ray->plane_y = old_plane_x * sin(-0.05) + ray->plane_y * cos(-0.05);
	}
	if (ray->keys.r_arr)
	{	
		double old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(0.05) - ray->dir_y * sin(0.05);
		ray->dir_y = old_dir_x * sin(0.05) + ray->dir_y * cos(0.05);
		double old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(0.05) - ray->plane_y * sin(0.05);
		ray->plane_y = old_plane_x * sin(0.05) + ray->plane_y * cos(0.05);
	}
}

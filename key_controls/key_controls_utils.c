/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 22:25:10 by deddara           #+#    #+#             */
/*   Updated: 2020/08/26 22:53:52 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

#ifdef BONUS

int		mouse_move(int x, int y, t_raycast *ray)
{
	static int	prev_x;
	if (y)
	{
		;
	}
	if (prev_x < x)
		r_arr_move(ray);
	else if (prev_x > x)
		l_arr_move(ray);
	prev_x = x;
	if (x < 10 || x > ray->map->x - 20)
	{
		prev_x = 0;
		mlx_mouse_move(ray->vars->win,
			ray->map->x / 2, ray->map->y / 2);
	}
	return (0);
}
#endif

int			esc_press(t_raycast *ray)
{
	mlx_destroy_window(ray->vars->mlx, ray->vars->win);
	shut_down_music();
	exit(0);
}

void		l_arr_move(t_raycast *ray)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(-0.05) - ray->dir_y * sin(-0.05);
	ray->dir_y = old_dir_x * sin(-0.05) + ray->dir_y * cos(-0.05);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(-0.05) - ray->plane_y * sin(-0.05);
	ray->plane_y = old_plane_x * sin(-0.05) + ray->plane_y * cos(-0.05);
}

void		r_arr_move(t_raycast *ray)
{
	double old_dir_x;
	double old_plane_x;
	
	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(0.05) - ray->dir_y * sin(0.05);
	ray->dir_y = old_dir_x * sin(0.05) + ray->dir_y * cos(0.05);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(0.05) - ray->plane_y * sin(0.05);
	ray->plane_y = old_plane_x * sin(0.05) + ray->plane_y * cos(0.05);
}

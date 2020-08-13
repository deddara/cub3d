/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:11:25 by deddara           #+#    #+#             */
/*   Updated: 2020/08/13 18:52:06 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

static void w_and_s_handler(t_raycast *ray)
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

static void	d_and_a_handler(t_raycast *ray)
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

static void	r_and_l_handler(t_raycast *ray)
{
	if (ray->keys.l_arr)
	{	
		double old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-ray->rotate_speed) - ray->dir_y * sin(-ray->rotate_speed);
		ray->dir_y = old_dir_x * sin(-ray->rotate_speed) + ray->dir_y * cos(-ray->rotate_speed);
		double old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-ray->rotate_speed) - ray->plane_y * sin(-ray->rotate_speed);
		ray->plane_y = old_plane_x * sin(-ray->rotate_speed) + ray->plane_y * cos(-ray->rotate_speed);
	}
	if (ray->keys.r_arr)
	{	
		double old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(ray->rotate_speed) - ray->dir_y * sin(ray->rotate_speed);
		ray->dir_y = old_dir_x * sin(ray->rotate_speed) + ray->dir_y * cos(ray->rotate_speed);
		double old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(ray->rotate_speed) - ray->plane_y * sin(ray->rotate_speed);
		ray->plane_y = old_plane_x * sin(ray->rotate_speed) + ray->plane_y * cos(ray->rotate_speed);
	}
}

int key_press(int keycode, t_raycast *ray)
{
	if (keycode == 13)
		ray->keys.w = 1;
	if (keycode == 1)
		ray->keys.s = 1;
	if (keycode == 0)
		ray->keys.a = 1;
	if (keycode == 2)
		ray->keys.d = 1;
	if (keycode == 123) //left
		ray->keys.l_arr = 1;
	if (keycode == 124)
		ray->keys.r_arr = 1;
	if (keycode == 53)
	{
		mlx_destroy_window(ray->vars->mlx, ray->vars->win);
		exit(0);
	}
	return (0);
}

int key_release(int keycode, t_raycast *ray)
{
	if (keycode == 13)/*W*/
		ray->keys.w = 0;
	if (keycode == 1)
		ray->keys.s = 0;
	if (keycode == 0)
		ray->keys.a = 0;
	if (keycode == 2)
		ray->keys.d = 0;
	if (keycode == 123) //left
		ray->keys.l_arr = 0;
	if (keycode == 124)
		ray->keys.r_arr = 0;
	return (0);
}

static void process_keys(t_raycast *ray)
{
	if (ray->keys.w || ray->keys.s)
		w_and_s_handler(ray);
	if (ray->keys.a || ray->keys.d)
		d_and_a_handler(ray);
	if (ray->keys.l_arr || ray->keys.r_arr)
		r_and_l_handler(ray);
}

int		key_controls(t_raycast *ray)
{
	process_keys(ray);
	mlx_destroy_image(ray->vars->mlx, ray->img->img);
	ray->img->img = mlx_new_image(ray->vars->mlx, ray->map->x, ray->map->y);
	ray->img->addr = mlx_get_data_addr(ray->img->img, &ray->img->bits_per_pixel, &ray->img->line_length,
                    	&ray->img->endian);
	paint_fc(ray->map, ray->img);
	ray_caster(ray->map, ray->img, ray);
	mlx_put_image_to_window(ray->vars->mlx, ray->vars->win, ray->img->img, 0, 0); 
	return (0);
}
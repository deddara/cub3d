/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:27:03 by deddara           #+#    #+#             */
/*   Updated: 2020/08/27 17:32:25 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

int			key_press(int keycode, t_raycast *ray)
{
	if (keycode == 13)
		ray->keys.w = 1;
	if (keycode == 1)
		ray->keys.s = 1;
	if (keycode == 0)
		ray->keys.a = 1;
	if (keycode == 2)
		ray->keys.d = 1;
	if (keycode == 123)
		ray->keys.l_arr = 1;
	if (keycode == 124)
		ray->keys.r_arr = 1;
	if (keycode == 53)
	{
		mlx_destroy_window(ray->vars->mlx, ray->vars->win);
		shut_down_music();
		exit(0);
	}
	if (keycode == 257)
		ray->keys.ctrl = 1;
	return (0);
}

int			key_release(int keycode, t_raycast *ray)
{
	if (keycode == 13)
		ray->keys.w = 0;
	if (keycode == 1)
		ray->keys.s = 0;
	if (keycode == 0)
		ray->keys.a = 0;
	if (keycode == 2)
		ray->keys.d = 0;
	if (keycode == 123)
		ray->keys.l_arr = 0;
	if (keycode == 124)
		ray->keys.r_arr = 0;
	if (keycode == 53)
		ray->keys.esc = 0;
	if (keycode == 257)
		ray->keys.ctrl = 0;
	return (0);
}

static void	process_keys(t_raycast *ray)
{
	if (ray->keys.w || ray->keys.s)
		w_and_s_handler(ray);
	if (ray->keys.a || ray->keys.d)
		d_and_a_handler(ray);
	if (ray->keys.l_arr || ray->keys.r_arr)
		r_and_l_handler(ray);
}

int			key_controls(t_raycast *ray)
{
	process_keys(ray);
	mlx_destroy_image(ray->vars->mlx, ray->img->img);
	ray->img->img = mlx_new_image(ray->vars->mlx, ray->map->x, ray->map->y);
	ray->img->addr = mlx_get_data_addr(ray->img->img,\
		&ray->img->bits_per_pixel, &ray->img->line_length, &ray->img->endian);
	paint_fc(ray, ray->img);
	ray_caster(ray->map, ray->img, ray);
	draw_health(ray);
	mlx_put_image_to_window(ray->vars->mlx, ray->vars->win,\
		ray->img->img, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 19:38:29 by deddara           #+#    #+#             */
/*   Updated: 2020/08/28 16:27:21 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static int		init(t_raycast *ray, t_map *map)
{
	int i;

	i = 0;
	if (!(ray->x_buffer = (double*)malloc(sizeof(double) * map->x)))
		return (0);
	ray->player_x = (double)map->x_player + 0.5;
	ray->player_y = (double)map->y_player + 0.5;
	ray->dlt_dist_x = 0;
	ray->dlt_dist_y = 0;
	sprites_count(ray, map);
	dir_calc(ray, map);
	return (1);
}

static void		keys_init(t_raycast *ray)
{
	ray->keys.w = 0;
	ray->keys.s = 0;
	ray->keys.a = 0;
	ray->keys.d = 0;
	ray->keys.l_arr = 0;
	ray->keys.r_arr = 0;
	ray->keys.esc = 0;
	ray->keys.ctrl = 0;
}

static int		win_init(t_vars *vars, t_data *img, t_map *map, char *argv)
{
	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &map->x, &map->y);
	if (!parser(map, argv))
		return (0);
	vars->win = mlx_new_window(vars->mlx, map->x, map->y, "Hello world!");
	img->img = mlx_new_image(vars->mlx, map->x, map->y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,\
	&img->line_length, &img->endian);
	return (1);
}

int				game(char **argv, int argc)
{
	t_data		img;
	t_vars		vars;
	t_map		map;
	t_raycast	ray;

	if (!(win_init(&vars, &img, &map, argv[1])))
		return (0);
	if (!init(&ray, &map))
		return (0);
	keys_init(&ray);
	ray.map = &map;
	ray.img = &img;
	ray.vars = &vars;
	take_textures(&ray);
	paint_fc(&ray, &img);
	ray_caster(&map, &img, &ray);
	if (argc == 3)
		return (make_scr(&ray, &img));
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &ray);
	mlx_hook(vars.win, 3, 1L << 1, key_release, &ray);
	mlx_hook(vars.win, 17, 1L << 17, esc_press, &ray);
	mlx_loop_hook(vars.mlx, key_controls, &ray);
	mlx_loop(vars.mlx);
	return (0);
}

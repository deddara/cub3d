/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 19:38:29 by deddara           #+#    #+#             */
/*   Updated: 2020/08/18 19:45:46 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void paint_fc(t_map *map, t_data *img)
{
	int y_c = 0;
	int x_c = 0;
	while (y_c < map->y / 2)
	{
		x_c = 0;
		while (x_c < map->x)
		{
			my_mlx_pixel_put(img, x_c, y_c, map->c_rgb);
			x_c++;
		}
		y_c++;
	}
	while(y_c < map->y)
	{
		x_c = 0;
		while (x_c < map->x)
		{
			my_mlx_pixel_put(img, x_c, y_c, map->f_rgb);
			x_c++;
		}
		y_c++;
	}
}
static int _init(t_raycast *ray, t_map *map)
{
	int i;

	i = 0;
	if(!(ray->x_buffer = (double*)malloc(sizeof(double) * map->x)))
		return (0);
	ray->player_x = (double)map->x_player + 0.5;
	ray->player_y = (double)map->y_player + 0.5;
	ray->dlt_dist_x = 0;
	ray->dlt_dist_y = 0;
	sprites_count(ray, map);
	dir_calc(ray, map);
	return (1);
}

static void keys_init (t_raycast *ray)
{
	ray->keys.w = 0;
	ray->keys.s = 0;
	ray->keys.a = 0;
	ray->keys.d = 0;
	ray->keys.l_arr = 0;
	ray->keys.r_arr = 0;
	ray->keys.esc = 0;
}

int			game(void)
{
    t_data		img;
    t_vars		vars;
    t_map		map;
	t_raycast	ray;
	parser(&map); //парсинг карты
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, map.x, map.y, "Hello world!");
    img.img = mlx_new_image(vars.mlx, map.x, map.y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);	
	paint_fc(&map, &img);
	if(!_init(&ray, &map))
		return (0);
	ray.map = &map;
	ray.img = &img;
	ray.vars = &vars;
	keys_init(&ray);
	ray_caster(&map, &img, &ray);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0); 
	mlx_hook(vars.win, 2, 1L << 0, key_press, &ray);
	mlx_hook(vars.win, 3, 1L << 1, key_release, &ray);
	mlx_loop_hook(vars.mlx, key_controls, &ray);
    mlx_loop(vars.mlx);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:22:20 by deddara           #+#    #+#             */
/*   Updated: 2020/08/09 21:24:11 by deddara          ###   ########.fr       */
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


//************************************************
//ОТРИСОВКА ПОТОЛКА И ПОЛА

static void paint_fc(t_map *map, t_data *img)
{
	int y_c = 0;
	int x_c = 0;
	while (y_c < map->y / 2)
	{
		x_c = 0;
		while (x_c < map->x)
		{
			my_mlx_pixel_put(img, x_c, y_c, 0x0000F9);
			x_c++;
		}
		y_c++;
	}
	while(y_c < map->y)
	{
		x_c = 0;
		while (x_c < map->x)
		{
			my_mlx_pixel_put(img, x_c, y_c, 0xFFFF41);
			x_c++;
		}
		y_c++;
	}
}

//ОТРИСОВКА ПОТОЛКА И ПОЛА
//************************************************
// static int skipper(t_map *map, int x, int y)
// {
// 	if (map->map[y][x] == ' ' || map->map[y][x] == '0' || map->map[y][x] == '2' || 
// 		map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'W'
// 		|| map->map[y][x] == 'E')
// 		return (1);
// 	return (0);
// }

// static void draw_rect(int x, int y, t_map *map, t_data *img)
// {
// 	int rect_x;
// 	int rect_y;
// 	int i, j;

// 	i = 0;
// 	j = 0;
	
// 	rect_x = x * (map->x / map->x_count / 3);
// 	rect_y = y * (map->y / map->y_count / 3);
	
// 	while (i < (map->x / map->x_count / 3) - 1)
// 	{
// 		j = 0;
// 	 	while (j < (map->y / map->y_count / 3) - 1)
// 		{
// 			my_mlx_pixel_put(img, rect_x + i, rect_y + j, 0xFFFF41);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void draw_player(int x, int y, t_map *map, t_data *img)
// {
// 	int rect_x;
// 	int rect_y;
// 	int i, j;

// 	i = 0;
// 	j = 0;
	
// 	rect_x = x * (map->x / map->x_count / 3) + ((map->x / map->x_count / 3) / 2);
// 	rect_y = y * (map->y / map->y_count / 3) + ((map->y / map->y_count / 3) / 2);
	
// 	while (i < 5)
// 	{
// 		j = 0;
// 	 	while (j < 5)
// 		{
// 			my_mlx_pixel_put(img, rect_x + i, rect_y + j, 0xFF0000);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void paint_map(t_map *map, t_data *img)
// {
// 	int x = 0;
// 	int y = 0;

// 	while (map->map[y])
// 	{
// 		x = 0;
// 		while (map->map[y][x])
// 		{
// 			if (skipper(map, x, y))
// 			{
// 				x++;
// 				continue ;
// 			}
// 			draw_rect(x, y, map, img);
// 			x++;
// 		}
// 		y++;
// 	}
// }

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

int             ft_close(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
    	mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
		ft_putnbr_fd(keycode, 0);
	return (0);
}
int             ft_close_2(int keycode, t_raycast *ray)
{
	if(keycode == 13)
	{
		if (skipper(ray->map, (int)ray->player_y, (int)ray->player_x + ray->dir_x))
		{

			// for (int i = 0; i < 1920 * 1080 * ray->img->bits_per_pixel / 8; i++)
			// {
			// 	ray->img->addr[i] = 0;
			// }
			// ray->img->addr = mlx_get_data_addr(ray->img->img, &ray->img->bits_per_pixel, &ray->img->line_length,
           	//                       &ray->img->endian);
			ray->player_x +=  ray->dir_x;
			ft_putnbr_fd(ray->player_x, 0);
		}
		if (skipper(ray->map, (int)ray->player_y + ray->dir_y, (int)ray->player_x ))
			ray->player_y +=  ray->dir_y;
		paint_fc(ray->map, ray->img);
		ray_caster(ray->map, ray->img, ray);	
		mlx_put_image_to_window(ray->vars->mlx, ray->vars->win, ray->img->img, 0, 0); 
	}
	if(keycode == 1)
	{
		if (skipper(ray->map, (int)ray->player_y, (int)ray->player_x - ray->dir_x))
			ray->player_x -=  ray->dir_x;
		if (skipper(ray->map, (int)ray->player_y - ray->dir_y, (int)ray->player_x ))
			ray->player_y -=  ray->dir_y;
		paint_fc(ray->map, ray->img);
		ray_caster(ray->map, ray->img, ray);
		mlx_put_image_to_window(ray->vars->mlx, ray->vars->win, ray->img->img, 0, 0); 
		ft_putnbr_fd(ray->player_x, 0);
	}
	if(keycode == 0)
	{	
		double old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(M_PI / 20) - ray->dir_y * sin(M_PI / 20);
		ray->dir_y = old_dir_x * sin(M_PI / 20) + ray->dir_y * cos(M_PI / 20);
		double old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(M_PI / 20) - ray->plane_y * sin(M_PI / 20);
		ray->plane_y = old_plane_x * sin(M_PI / 20) + ray->plane_y * cos(M_PI / 20);
		paint_fc(ray->map, ray->img);
		ray_caster(ray->map, ray->img, ray);
		mlx_put_image_to_window(ray->vars->mlx, ray->vars->win, ray->img->img, 0, 0); 
	}
	if(keycode == 2)
	{	
		double old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-M_PI / 20) - ray->dir_y * sin(-M_PI / 20);
		ray->dir_y = old_dir_x * sin(-M_PI / 20) + ray->dir_y * cos(-M_PI / 20);
		double old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-M_PI / 20) - ray->plane_y * sin(-M_PI / 20);
		ray->plane_y = old_plane_x * sin(-M_PI / 20) + ray->plane_y * cos(-M_PI / 20);
		paint_fc(ray->map, ray->img);
		ray_caster(ray->map, ray->img, ray);
		mlx_put_image_to_window(ray->vars->mlx, ray->vars->win, ray->img->img, 0, 0); 
	}
	return (0);
}


int             main(void)
{
    t_data  img;
    t_vars vars;
    t_map map;
	t_raycast ray;
    // int x;
    // int y;
	parser(&map); //парсинг карты
    // x = 5;
    // y = 5;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, map.x, map.y, "Hello world!");
    img.img = mlx_new_image(vars.mlx, map.x, map.y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	
	paint_fc(&map, &img);
	_init(&ray, &map);
	// paint_map(&map, &img);
	// draw_player(map.x_player, map.y_player, &map, &img);
	ray.map = &map;
	ray.img = &img;
	ray.vars = &vars;
	ray_caster(&map, &img, &ray);
	//mlx_key_hook(vars.win, ft_close, &vars);
	mlx_key_hook(vars.win, ft_close_2, &ray);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0); 
    mlx_loop(vars.mlx);
	return (0);
}
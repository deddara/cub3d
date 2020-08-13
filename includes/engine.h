/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 14:47:52 by deddara           #+#    #+#             */
/*   Updated: 2020/08/13 17:34:32 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# include "main.h"

# define ANGLE 66

typedef struct t_keys
{
	int w;
	int a;
	int s;
	int d;
	int esc;
	int l_arr;
	int r_arr;
}				t_keys;

typedef struct s_raycast
{
	double	camera_x;
	double		dir_x;
	double		dir_y;
	double	plane_x;
	double	plane_y;
	double	dist_x;
	double	dist_y;
	double	dlt_dist_x;
	double	dlt_dist_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double	player_x;
	double	player_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int 	wall_side;
	double		wall_dist;
	int		wall_height;
	int		wall_start;
	int		wall_end;
	int		hit;
	t_data *img;
	t_map *map;
	t_vars *vars;
	double		frame_time;
	double		move_speed;
	double		rotate_speed;
		double		time_curr;
	double		time_prev;
	t_data txtr_no;
	t_data txtr_so;
	t_data txtr_we;
	t_data txtr_ea;
	t_keys	keys;
}				t_raycast;


int skipper(t_map *map, int y, int x);
void	ray_caster(t_map *map, t_data *img, t_raycast *ray);
void dir_calc(t_raycast *ray, t_map *map);
int			key_press(int keycode, t_raycast *ray);
int			key_release(int keycode, t_raycast *ray);
int 		key_controls(t_raycast *ray);


#endif
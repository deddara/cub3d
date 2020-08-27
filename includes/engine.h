/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 14:47:52 by deddara           #+#    #+#             */
/*   Updated: 2020/08/27 13:42:58 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "main.h"
# define ANGLE 66
# define UDIV 0.7
# define VDIV 0.7
# define VMOVE 128

typedef struct	s_sprite
{
	int				id;
	double			x;
	double			y;
	double			dist;
	int				flag;
	struct s_sprite	*next;
	struct s_sprite	*prev;
}				t_sprite;

typedef struct	s_counters
{
	int		i;
	int		j;
	int		flag;
}				t_counters;

typedef struct	s_spaint
{
	double	spr_x;
	double	spr_y;
	double	inv_det;
	double	trnsfrm_x;
	double	trnsfrm_y;
	int		spr_scr_x;
	int		v_move_scr;
	int		spr_h;
	int		start_y;
	int		start_x;
	int		end_y;
	int		end_x;
	int		tex_x;
	int		tex_y;
	int		spr_w;
}				t_spaint;

typedef struct	s_keys
{
	int w;
	int a;
	int s;
	int d;
	int esc;
	int l_arr;
	int r_arr;
	int	ctrl;
}				t_keys;

typedef struct	s_paint
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		tex_h;
	int		tex_w;
	double	step;
	double	tex_pos;
}				t_paint;

typedef struct	s_raycast
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		dist_x;
	double		dist_y;
	double		dlt_dist_x;
	double		dlt_dist_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		player_x;
	double		player_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			wall_side;
	double		wall_dist;
	int			wall_height;
	int			wall_start;
	int			wall_end;
	int			hit;
	t_data		*img;
	t_map		*map;
	t_vars		*vars;
	double		frame_time;
	double		move_speed;
	double		rotate_speed;
	double		time_curr;
	double		time_prev;
	t_data		txtr_no;
	t_data		txtr_so;
	t_data		txtr_we;
	t_data		txtr_ea;
	t_data		txtr_s;
	t_keys		keys;
	t_sprite	*sprite;
	double		*x_buffer;
}				t_raycast;

int				skipper(t_map *map, int y, int x);
void			ray_caster(t_map *map, t_data *img, t_raycast *ray);
void			dir_calc(t_raycast *ray, t_map *map);
int				key_press(int keycode, t_raycast *ray);
int				key_release(int keycode, t_raycast *ray);
int				key_controls(t_raycast *ray);
void			paint_fc(t_raycast *ray, t_data *img);
void			sprites_count(t_raycast *ray, t_map *map);
void			sprite_handler(t_raycast *ray);
int				getpixelcolor(t_data *img, int x, int y);
void			paint_map(t_raycast *ray, t_map *map, t_data *img, int x);
void			sprite_painter(t_raycast *ray, t_sprite *sprite_data);
void			add_sprite(t_sprite *sprite, int y, int x, int id);
t_sprite		*new_sprite(int y, int x);
void			r_and_l_handler(t_raycast *ray);
void			d_and_a_handler(t_raycast *ray);
void			w_and_s_handler(t_raycast *ray);
int				make_scr(t_raycast *ray, t_data *img);
int				shut_down_music(void);
int				esc_press(t_raycast *ray);
void			l_arr_move(t_raycast *ray);
int				mouse_move(int x, int y, t_raycast *ray);
void			r_arr_move(t_raycast *ray);
int				draw_health(t_raycast *ray);
#endif

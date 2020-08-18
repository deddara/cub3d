/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_painter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:22:49 by deddara           #+#    #+#             */
/*   Updated: 2020/08/18 15:46:56 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

static void	draw__sprite_y(t_spaint *spaint, t_raycast *ray, int stripe)
{
	int	y;
	int d;
	int color;

	y = spaint->start_y;
	while (y < spaint->end_y)
	{
		d = (y - spaint->v_move_scr) * 256 - ray->map->y * 128 +\
			spaint->spr_h * 128;
		spaint->tex_y = ((d * ray->txtr_s.height)\
			/ spaint->spr_h) / 256;
		color = getpixelcolor(&ray->txtr_s, spaint->tex_x, spaint->tex_y);
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(ray->img, stripe, y, color);
		y++;
	}
}

static void	draw_sprite(t_spaint *spaint, t_raycast *ray)
{
	int	stripe;

	stripe = spaint->start_x;
	while (stripe < spaint->end_x)
	{
		spaint->tex_x = (int)(256 * (stripe - (-spaint->spr_w / 2 + \
		spaint->spr_scr_x)) * ray->txtr_s.width / spaint->spr_w) / 256;
		if (spaint->trnsfrm_y > 0 && stripe > 0 && stripe < ray->map->x &&\
			spaint->trnsfrm_y < ray->x_buffer[stripe])
			draw__sprite_y(spaint, ray, stripe);
		stripe++;
	}
}

static void	y_calcs(t_raycast *ray, t_spaint *spaint)
{
	spaint->start_y = -spaint->spr_h / 2 + ray->map->y / 2 + spaint->v_move_scr;
	if (spaint->start_y < 0)
		spaint->start_y = 0;
	spaint->end_y = spaint->spr_h / 2 + ray->map->y / 2 + spaint->v_move_scr;
	if (spaint->end_y >= ray->map->y)
		spaint->end_y = ray->map->y - 1;
}

void		sprite_painter(t_raycast *ray, t_sprite *sprite_data)
{
	t_spaint spaint;

	spaint.spr_x = sprite_data->x - ray->player_x;
	spaint.spr_y = sprite_data->y - ray->player_y;
	spaint.inv_det = 1.0 / \
		(ray->plane_x * ray->dir_y - ray->dir_x * ray->plane_y);
	spaint.trnsfrm_x = spaint.inv_det * \
		(ray->dir_y * spaint.spr_x - ray->dir_x * spaint.spr_y);
	spaint.trnsfrm_y = spaint.inv_det * \
		(-ray->plane_y * spaint.spr_x + ray->plane_x * spaint.spr_y);
	spaint.spr_scr_x = (int)((ray->map->x / 2) * \
		(1 + spaint.trnsfrm_x / spaint.trnsfrm_y));
	spaint.v_move_scr = (int)(VMOVE / spaint.trnsfrm_y);
	spaint.spr_h = abs((int)(((ray->map->y / (spaint.trnsfrm_y))) * VDIV));
	y_calcs(ray, &spaint);
	spaint.spr_w = abs((int)(((ray->map->y / (spaint.trnsfrm_y))) * UDIV));
	spaint.start_x = -spaint.spr_w / 2 + spaint.spr_scr_x;
	if (spaint.start_x < 0)
		spaint.start_x = 0;
	spaint.end_x = spaint.spr_w / 2 + spaint.spr_scr_x;
	if (spaint.end_x >= ray->map->x)
		spaint.end_x = ray->map->x - 1;
	draw_sprite(&spaint, ray);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_cl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 19:52:19 by deddara           #+#    #+#             */
/*   Updated: 2020/08/27 17:36:17 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

void		paint_fc(t_raycast *ray, t_data *img)
{
	t_counters	coords;
	int			draw_end;

	coords.i = 0;
	draw_end = !ray->keys.ctrl ? ray->map->y / 2 : ray->map->y / 3;
	while (coords.i < draw_end)
	{
		coords.j = 0;
		while (coords.j < ray->map->x)
		{
			my_mlx_pixel_put(img, coords.j, coords.i, ray->map->c_rgb);
			coords.j++;
		}
		coords.i++;
	}
	while (coords.i < ray->map->y)
	{
		coords.j = 0;
		while (coords.j < ray->map->x)
		{
			my_mlx_pixel_put(img, coords.j, coords.i, ray->map->f_rgb);
			coords.j++;
		}
		coords.i++;
	}
}
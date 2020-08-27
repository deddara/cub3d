/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:35:57 by deddara           #+#    #+#             */
/*   Updated: 2020/08/27 17:21:06 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "main.h"

int		draw_health(t_raycast *ray)
{
	int y;
	int x;
	int pixel;
	
	y = 0;
	while (y < ray->map->y / 7)
	{	
		x = 0;
		while (x < ray->map->x / 5)
		{
			pixel = getpixelcolor(&ray->health, (int)((double)((x / (double)(ray->map->x / 5)) * ray->health.width)),\
			(int)((double)((y / (double)(ray->map->y / 7)) * ray->health.height)));
			if ((pixel & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(ray->img, ray->map->x - x, y, pixel);
			x++;
		}
		y++;
	}
	return (1);
}
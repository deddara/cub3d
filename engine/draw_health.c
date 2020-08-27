/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:35:57 by deddara           #+#    #+#             */
/*   Updated: 2020/08/27 15:46:57 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "main.h"

int		draw_health(t_raycast *ray)
{
	t_data health;
	int y;
	int x;
	int pixel;
	int y1 = 0;
	int x1;
	y = 0;
	x = 0;
	if(!(health.img = mlx_png_file_to_image(ray->vars->mlx, "./pics/unnamed.png",\
	&health.width, &health.height)))
		return (0);
	if(!(health.addr = mlx_get_data_addr(health.img,\
		&health.bits_per_pixel, &health.line_length, &health.endian)))
		return (0);
	while (y < health.height)
	{	
		x = 0;
		x1 = 0;
		while (x < health.width)
		{
			pixel = getpixelcolor(&health, x , y);
			if ((pixel & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(ray->img, x1, y1, pixel);
			x += ray->map->x / health.width * 1.5 ;
			x1++;
		}
		y1++;
		y += ray->map->y /  health.height * 1;
	}
	return (1);
}
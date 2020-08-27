/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:35:57 by deddara           #+#    #+#             */
/*   Updated: 2020/08/27 13:43:02 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "main.h"

int		draw_health(t_raycast *ray)
{
	t_data health;

	if(!(health.img = mlx_png_file_to_image(ray->vars->mlx, "pack.png",\
	&ray->txtr_ea.width, &ray->txtr_ea.height)))
		return (0);
	if(!(health.addr = mlx_get_data_addr(health.img,\
		&health.bits_per_pixel, &health.line_length, &health.endian)))
		return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:28:28 by deddara           #+#    #+#             */
/*   Updated: 2020/08/28 16:51:21 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

static int	take_addr(t_raycast *ray)
{
	if (!(ray->txtr_so.addr = mlx_get_data_addr(ray->txtr_so.img, \
	&ray->txtr_so.bits_per_pixel, &ray->txtr_so.line_length, \
	&ray->txtr_so.endian)))
		return (0);
	if (!(ray->txtr_no.addr = mlx_get_data_addr(ray->txtr_no.img, \
	&ray->txtr_no.bits_per_pixel, &ray->txtr_no.line_length, \
	&ray->txtr_no.endian)))
		return (0);
	if (!(ray->txtr_ea.addr = mlx_get_data_addr(ray->txtr_ea.img,\
	&ray->txtr_ea.bits_per_pixel,\
	&ray->txtr_ea.line_length, &ray->txtr_ea.endian)))
		return (0);
	if (!(ray->txtr_we.addr = mlx_get_data_addr(ray->txtr_we.img,\
	&ray->txtr_we.bits_per_pixel, \
	&ray->txtr_we.line_length, &ray->txtr_we.endian)))
		return (0);
	if (!(ray->txtr_s.addr = mlx_get_data_addr(ray->txtr_s.img,\
	&ray->txtr_s.bits_per_pixel,\
	&ray->txtr_s.line_length, &ray->txtr_s.endian)))
		return (0);
	if (!(ray->health.addr = mlx_get_data_addr(ray->health.img,\
	&ray->health.bits_per_pixel, &ray->health.line_length, \
	&ray->health.endian)))
		return (0);
	return (1);
}

int			take_textures(t_raycast *ray)
{
	if (!(ray->txtr_so.img = mlx_xpm_file_to_image(ray->vars->mlx,\
	ray->map->so, &ray->txtr_so.width, &ray->txtr_so.height)))
		return (0);
	if (!(ray->txtr_no.img = mlx_xpm_file_to_image(ray->vars->mlx,\
	ray->map->no, &ray->txtr_no.width, &ray->txtr_no.height)))
		return (0);
	if (!(ray->txtr_ea.img = mlx_xpm_file_to_image(ray->vars->mlx,\
	ray->map->ea, &ray->txtr_ea.width, &ray->txtr_ea.height)))
		return (0);
	if (!(ray->txtr_we.img = mlx_xpm_file_to_image(ray->vars->mlx,\
	ray->map->we, &ray->txtr_we.width, &ray->txtr_we.height)))
		return (0);
	if (!(ray->txtr_s.img = mlx_xpm_file_to_image(ray->vars->mlx,\
	ray->map->s, &ray->txtr_s.width, &ray->txtr_s.height)))
		return (0);
	if (!(ray->health.img = mlx_png_file_to_image(ray->vars->mlx,\
	"./pics/unnamed.png", &ray->health.width, &ray->health.height)))
		return (0);
	if (!take_addr(ray))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:57:47 by deddara           #+#    #+#             */
/*   Updated: 2020/08/25 17:32:04 by deddara          ###   ########.fr       */
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

int			getpixelcolor(t_data *img, int x, int y)
{
	if (!img->width || !img->height)
		return (0);
	x = abs(x);
	y = abs(y);
	if (x > img->width || y > img->height || x < 0 || y < 0)
		return (0);
	return (*(int*)(img->addr + ((x + (y * img->width))\
		* (img->bits_per_pixel / 8))));
}

int			skipper(t_map *map, int y, int x)
{
	if (map->map[y][x] == ' ' || map->map[y][x] == '0' || map->map[y][x] == '2'
	|| map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'W'
		|| map->map[y][x] == 'E')
		return (1);
	return (0);
}

t_sprite	*new_sprite(int y, int x)
{
	t_sprite *sprite;

	if (!(sprite = malloc(sizeof(t_sprite) * 1)))
		return (NULL);
	sprite->y = (double)y + 0.5;
	sprite->x = (double)x + 0.5;
	sprite->dist = 0.0;
	sprite->id = 0;
	sprite->prev = NULL;
	sprite->next = NULL;
	return (sprite);
}

void		add_sprite(t_sprite *sprite, int y, int x, int id)
{
	t_sprite *tmp;
	t_sprite *new;

	if (!(new = malloc(sizeof(t_sprite) * 1)))
		return ;
	new->y = (double)y + 0.5;
	new->x = (double)x + 0.5;
	new->id = id;
	new->dist = 0.0;
	tmp = sprite;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
}

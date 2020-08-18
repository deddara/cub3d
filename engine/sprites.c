/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:19:45 by deddara           #+#    #+#             */
/*   Updated: 2020/08/18 14:33:03 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	list_swap(t_sprite *tmp, t_sprite *a)
{
	int		t;
	double	j;

	t = 0;
	t = tmp->id;
	tmp->id = a->id;
	a->id = t;
	j = tmp->x;
	tmp->x = a->x;
	a->x = j;
	j = tmp->y;
	tmp->y = a->y;
	a->y = j;
	j = tmp->dist;
	tmp->dist = a->dist;
	a->dist = j;
}

static void	sprites_sort(t_raycast *ray)
{
	t_sprite	*tmp;
	t_sprite	*a;
	int			flag;

	flag = 1;
	while (flag)
	{
		tmp = ray->sprite;
		a = tmp->next;
		flag = 0;
		while (a)
		{
			if ((tmp->dist) < (a->dist))
			{
				list_swap(tmp, a);
				flag = 1;
			}
			tmp = tmp->next;
			a = a->next;
		}
	}
}

void		sprites_count(t_raycast *ray, t_map *map)
{
	t_counters	count;
	t_sprite	*sprite;

	count.flag = 0;
	count.i = 0;
	while (map->map[count.i])
	{
		count.j = 0;
		while (map->map[count.i][count.j])
		{
			if (map->map[count.i][count.j] == '2' && count.flag == 0)
			{
				sprite = new_sprite(count.i, count.j);
				count.flag++;
			}
			else if (map->map[count.i][count.j] == '2' && count.flag)
			{
				add_sprite(sprite, count.i, count.j, count.flag);
				count.flag++;
			}
			count.j++;
		}
		count.i++;
	}
	ray->sprite = sprite;
}

static void	sprite_dist_calc(t_raycast *ray)
{
	t_sprite	*sp;

	sp = ray->sprite;
	while (sp)
	{
		sp->dist = sqrt(pow(ray->player_x - sp->x, 2) + \
						pow(ray->player_y - sp->y, 2));
		sp = sp->next;
	}
}

void		sprite_handler(t_raycast *ray)
{
	t_sprite *tmp;

	sprite_dist_calc(ray);
	sprites_sort(ray);
	tmp = ray->sprite;
	while (tmp)
	{
		sprite_painter(ray, tmp);
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:19:45 by deddara           #+#    #+#             */
/*   Updated: 2020/08/13 19:28:26 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_sprite	*new_sprite(int y, int x)
{
	t_sprite *sprite;

	if (!(sprite = malloc(sizeof(t_sprite) * 1)))
		return NULL;
	sprite->y = y;
	sprite->x = x;
	sprite->id = 0;
	sprite->prev = NULL;
	sprite->next = NULL;
	return (sprite);
}

static void add_sprite(t_sprite *sprite, int y, int x, int id)
{
	t_sprite *tmp;
	t_sprite *new;

	if (!(new = malloc(sizeof(t_sprite) * 1)))
		return ;
	new->y = y;
	new->x = x;
	new->id = id;
	new->dist = 0;
	tmp = sprite;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
}

void		sprites_count(t_raycast *ray, t_map *map)
{
	int			i;
	int			j;
	int			flag;
	t_sprite	*sprite;

	flag = 0;
	i = 1;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '2' && flag == 0)
			{
				sprite = new_sprite(i , j);
				flag++;
			}
			else if (map->map[i][j] == '2' && flag)
			{
				add_sprite(sprite, i, j, flag);
				flag++;
			}
			j++;
		}
		i++;
	}
	ray->sprite = sprite;
}
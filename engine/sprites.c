/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:19:45 by deddara           #+#    #+#             */
/*   Updated: 2020/08/13 20:42:06 by deddara          ###   ########.fr       */
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

void sprites_sort(t_raycast *ray)
{
 	t_sprite *tmp;
    t_sprite *a;
    int flag=1;
    while(flag==1)
    {
        tmp=ray->sprite;
        a=tmp->next;
        flag=0;
        while(a)
        {
            if((tmp->dist)<(a->dist))
            {
				list_swap(tmp, a);
                flag=1;
            }
            tmp=tmp->next;
            a=a->next;
        }
    }
}

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

static void sprite_dist_calc(t_raycast *ray)
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

void	sprite_handler(t_raycast *ray)
{
	int flags;
	sprite_dist_calc(ray);
	sprites_sort(ray);
	flags = 3;
	flags = 4;
}
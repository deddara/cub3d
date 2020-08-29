/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 21:34:44 by deddara           #+#    #+#             */
/*   Updated: 2020/08/29 18:07:51 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include "engine.h"

void			ray_clr(t_raycast *ray)
{
	t_sprite *tmp;
	t_sprite *var;

	if (ray->sprite)
	{
		tmp = ray->sprite;
		while (tmp)
		{
			var = tmp->next;
			free(tmp);
			tmp = var;
		}
		ray->sprite = NULL;
	}
	if (ray->x_buffer)
		free(ray->x_buffer);
}

void			map_clr(t_map *map)
{
	int i;

	i = 0;
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->s)
		free(map->s);
	if (map->map_line)
		free(map->map_line);
	if (map->map)
	{
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
}

int				error_handler(t_map *map, char *line, int code)
{
	if (code == 1)
		ft_putstr_fd("==INVALID FILE==", 0);
	else if (code == 2)
		ft_putstr_fd("==MALLOC ERROR==", 0);
	else if (code == 3)
	{
		ft_putstr_fd("==PARAMS ERROR==\n--->", 0);
		ft_putstr_fd(line, 0);
	}
	else if (code == 4)
	{
		ft_putstr_fd("==MAP ERROR==\n--->", 0);
	}
	else if (code == 5)
	{
		ft_putstr_fd("==MAP ERROR==\n--->", 0);
	}
	free_line(line);
	map_clr(map);
	return (0);
}

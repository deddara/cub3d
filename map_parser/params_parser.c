/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:51:53 by deddara           #+#    #+#             */
/*   Updated: 2020/08/29 17:33:21 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

void		free_line(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
}

static int	r_checker(char *line, t_map *map)
{
	int i;
	int x;
	int y;

	i = 0;
	map->count++;
	if (!check_is_alone(line))
		return (0);
	if (!(map->r = ft_split(line, ' ')))
		return (0);
	while (map->r[i])
		i++;
	if (i != 3 || !(check_int(map->r[1]) || !(check_int(map->r[2])))
	|| !(y = ft_atoi(map->r[2])))
		return (0);
	if (!(x = ft_atoi(map->r[1])))
		return (0);
	map->x = (map->x >= x) ? x : map->x;
	map->y = (map->y >= y) ? y : map->y;
	freesher(map->r);
	return (1);
}

int			check_elems(char *line, t_map *map)
{
	if (line[0] == 'R')
		return (((r_checker(line, map))));
	else if (line[0] == 'N' && line[1] == 'O')
		return ((no_checker(line, map)));
	else if (line[0] == 'S' && line[1] == 'O')
		return ((so_checker(line, map)));
	else if (line[0] == 'W' && line[1] == 'E')
		return (((we_checker(line, map))));
	else if (line[0] == 'E' && line[1] == 'A')
		return (((ea_checker(line, map))));
	else if (line[0] == 'S' && line[1] == ' ')
		return ((s_checker(line, map)));
	else if (line[0] == 'F' && line[1] == ' ')
		return ((f_checker(line, map)));
	else if (line[0] == 'C' && line[1] == ' ')
		return ((c_checker(line, map)));
	else
		return (0);
	return (1);
}

static int	check_all_params(t_map *map)
{
	if (map->x == 0 || map->y == 0 || map->count != 8 || map->no == NULL ||
	map->so == NULL || map->we == NULL || map->ea == NULL || map->s == NULL
	|| map->f_rgb == (unsigned long)-1 || map->c_rgb == (unsigned long)-1)
		return (0);
	return (1);
}

int			params_parser(char *line, t_map *map, int fd)
{
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free_line(line);
			continue ;
		}
		if (!(check_elems(line, map)))
			return (error_handler(map, line, 3));
		if (map->count == 8)
			break ;
		free_line(line);
	}
	free_line(line);
	if (!(check_all_params(map)))
		return (error_handler(map, line, 3));
	return (1);
}

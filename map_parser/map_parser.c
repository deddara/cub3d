/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 03:49:06 by deddara           #+#    #+#             */
/*   Updated: 2020/07/29 04:16:45 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

int	map_parser(t_map *map)
{
	int i;
	int j;

	i = 1;
	if (!(map->map = ft_split(map->map_line, '\n')))
		return (0);
	if (!(first_last(map->map[map->y_count - 1], (void*) 0)))
		return (0);
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] && map->map[i][j] != '\n')
		{
			if (map->map[i][j] == ' ' && (map->map[i - 1][j] == '0' || map->map[i - 1][j] == '2'
				|| map->map[i - 1][j] == 'N' || map->map[i - 1][j] == 'S' || map->map[i - 1][j] == 'W'
					|| map->map[i - 1][j] == 'E'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
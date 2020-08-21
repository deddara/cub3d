/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 03:49:06 by deddara           #+#    #+#             */
/*   Updated: 2020/08/21 17:12:13 by deddara          ###   ########.fr       */
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
	free (map->map_line);
	map->map_line = NULL;
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
			if ((map->map[i][j] == '0' && (map->map[i - 1][j] == ' ')) ||
				(map->map[i][j] == '0' && !(map->map[i - 1][j])) || (map->map[i][j] == '0' && !(map->map[i + 1][j])))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int map_start_parser(char *line, t_map *map, int fd)
{
	ft_putstr_fd("f", 0);
	get_next_line(fd, &line);
	if ((line[0] == ' ' || line[0] == '1'))
		return (error_handler(map, 0, 5));
	free_line(line);
	ft_putstr_fd("s", 0);
	while(get_next_line(fd, &line) > 0)
	{
		if(line[0] == '\0' && map->y_count == 0)
		{	
			free_line(line);
			continue;
		}
		else if ((line && line[0] != ' ' && line[0] != '1')&& map->y_count != 0)
			return (error_handler(map, line, 4));
		if(!(map_line_parser(line, map)))
			return (error_handler(map, line, 4));
		free_line(line);
	}
	if ((line && line[0] != ' ' && line[0] != '1')&& map->y_count != 0)
		return (error_handler(map, line, 4));	
	if(!(map_line_parser(line, map)))
		return (error_handler(map, line, 4));
	free_line(line);
	if(!(map_parser(map)))
		return (error_handler(map, 0, 5));
	return (1);
}
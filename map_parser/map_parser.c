/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 20:53:16 by deddara           #+#    #+#             */
/*   Updated: 2020/07/27 22:36:13 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
//int		check_elems(char *line, t_map *map)
//{
//	if (line[0] == 'R')
	//{
		//map->count++;
		//map->r = ft_split(line, ' ');
	//}
	//return (0);
//}

int		map_parser(t_map *map)
{
	int		fd;
	char	*line;

	map = NULL;
	line = NULL;
	fd = open("/Users/deddara/school21/cub3d/cub3d_github/example_map.cub", O_RDONLY);
	if (!(map = ft_lstmapnew()))
		return (0);
	while(get_next_line(fd, &line))
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free (line);
	return (0);
}
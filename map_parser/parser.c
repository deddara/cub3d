/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 20:53:16 by deddara           #+#    #+#             */
/*   Updated: 2020/08/21 17:09:58 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
# include <math.h>

static int get_angle(t_map *map)
{
	if (map->player_pos == 'N')
		map->a_player = 3 * M_PI / 2;
	else if (map->player_pos == 'S')
		map->a_player = M_PI / 2;
	else if (map->player_pos == 'E')
		map->a_player = 0;
	else if (map->player_pos == 'W')
		map->a_player = M_PI;
	else
	{
		ft_putstr_fd("no player on map", 0);
		return (0);
	}
	return (1);
}

static void longest_width(t_map *map)
{
	int y;

	y = 0;
	int len;
	int prev_len;

	len = 0;
	while (map->map[y])
	{	
		prev_len = len;
		len = ft_strlen(map->map[y]);
		if (prev_len < len)
			prev_len = len;
		y++;
	}
	map->x_count = prev_len;
}

int		parser(t_map *map, char *argv)
{
	int		fd;
	char	*line;

	line = NULL;
	if((fd = open(argv, O_RDONLY)) < 0)
		return (error_handler(0, 0, 1));
	if(!ft_lstmapnew(map))
		return (error_handler(0, 0, 2));
	if(!(params_parser(line, map, fd)) || !(map_start_parser(line, map, fd)))
		return (0);
	if(!get_angle(map))
		return(0);
	longest_width(map);
	return (1);
}
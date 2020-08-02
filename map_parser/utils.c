/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:41:07 by deddara           #+#    #+#             */
/*   Updated: 2020/08/02 19:09:11 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

int	ft_lstmapnew(t_map *map)
{
    map->count = 0;
	map->x = 0;
	map->y = 0; 
    map->no = NULL;
    map->so = NULL;
    map->we = NULL;
    map->ea = NULL;
    map->s = NULL;
    map->c_rgb = -1;
	map->f_rgb = -1;
	map->y_count = 0;
	map->player_pos = '0';
	if(!(map->map_line = (char*)malloc(sizeof(char) * 1)))
		return (0);
	map->map_line[0] = '\0';
    map->no = NULL;
	map->a_player = 0;
	map->x_player = 0;
	map->y_player = 0;
	return (1);
}

int check_int(char *str)
{
	while(*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
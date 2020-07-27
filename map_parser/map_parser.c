/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 20:53:16 by deddara           #+#    #+#             */
/*   Updated: 2020/07/27 17:51:26 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

int check_elems(char *line, t_map *map)
{
    line = "dsa";
    map->x = 3;
    // if (line[0] == 'R')
    // {
    //     map->count++;

    // }
    // if (line[0] == 'N' && line[1] == 'O')
    // {
    //     map->count++;

    // }
    // if (line[0] == 'S' && line[1] = 'O')
    // {
    //     map->count++;

    // }
    // if (line[0] == 'W' && line[1] = 'E')
    // {
    //     map->count++;

    // }
    // if (line[0] == 'E' && line[1] = 'A')
    // {
    //     map->count++;

    // }
    // if (line[0] == 'S')
    // {
    //     map->count++;

    // }
    // if (line[0] == 'F')
    // {
    //     map->count++;

    // }
    // if (line[0] == 'C')
    // {
    //     map->count++;

    // }
    return (0);
}

int map_parser(t_map *map)
{
    // int fd;
     char *line;
    line = NULL;
    // line = NULL;
    // fd = open("../example_map.cub", O_RDONLY);
    // if (!map = ft_lstmapnew())
    //     return (0);
    // while (get_next_line(fd, &line))
    // {   
    //     if (line[0] = '\n')
    //         continue ;
         check_elems(line, map);
    // }
    return (1);
}
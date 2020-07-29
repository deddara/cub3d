/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 01:54:32 by deddara           #+#    #+#             */
/*   Updated: 2020/07/29 03:33:46 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

static int map_join(char *line, t_map *map)
{
	char	*tmp_map_line;
	char	*tmp_line;

	tmp_map_line = map->map_line;
	if (!(tmp_line = ft_strjoin(line, "\n")))
	{
		write(1, "d", 1);
		return (0);
	
	}
	if (!(map->map_line = ft_strjoin(map->map_line, tmp_line)))
	{
		write(1, "d", 1);
		return (0);
	}
	free(tmp_map_line);
	free(tmp_line);
	return (1);
}

static int first_last(char *line, t_map *map)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	if (!(map_join(line, map)))
		return (0);
	return (1);
}

static int line_check(char *line, t_map *map)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	map->y_count++;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != 'N' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != 'S' && line[i] != '2' && line[i] != '0')
			return (0);
		if ((line[i] == '0' || line[i] == '2' || line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'S' || line[i] == 'W') && flag == 0)
			return (0);
		if (line[i] == '1')
			flag++;
		if (line[i] == ' ' && !flag)
		{
			i++;
			continue ;
		}
		if (line[i] == ' ')
		{
			if ((line[i - 1] != ' ' && line[i - 1] != '1') || (line[i + 1] != ' ' && line[i + 1] != '1'))
				return (0);
		}
		if ((line[i] == 'N' || line[i] == 'E' || line[i] == 'S' || line[i] == 'W') && map->player_pos == '0')
			map->player_pos = line[i];
		else if ((line[i] == 'N' || line[i] == 'E' || line[i] == 'S' || line[i] == 'W') && map->player_pos != '0')
			return (0);
		i++;
	}
	return (1);
}

int map_parser(char *line, t_map *map)
{
	if(map->y_count == 0)
	{
		map->y_count++;
		if(!first_last(line, map))
			return (0);
		return (1);
	}
	if (!(line_check(line, map)))
		return (0);
	return (1);
}
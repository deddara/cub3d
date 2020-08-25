/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:41:07 by deddara           #+#    #+#             */
/*   Updated: 2020/08/25 13:46:53 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

int	ft_lstmapnew(t_map *map)
{
    map->count = 0;
	map->x = 0;
	map->y = 0;
	map->r = NULL; 
    map->no = NULL;
    map->so = NULL;
    map->we = NULL;
    map->ea = NULL;
    map->s = NULL;
    map->c_rgb = -1;
	map->f_rgb = -1;
	map->y_count = 0;
	map->x_count = 0;
	map->player_pos = '0';
	if (!(map->map_line = ft_strdup("")))
		return (0);
	map->map = NULL;
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

static int	ft_isspace(int c)
{
	if (c == '\n' || c == '\t' || c == '\v' || \
			c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

void	f_skip_spaces(char *line, int *i)
{
	while (ft_isspace(line[*i]))
		(*i)++;
}
int		f_cub3d_atoi(char *line, int *i)
{
	long long int	result;
	int				sign;

	sign = 1;
	result = 0;
	f_skip_spaces(line, i);
	if (line[*i] == '-')
		sign = -1;
	if (line[*i] == '-' || line[*i] == '+')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		if ((result * 10) < result)
			return (sign < 0 ? 0 : -1);
		result = result * 10 + line[*i] - '0';
		(*i)++;
	}
	return ((int)result * (int)sign);
}
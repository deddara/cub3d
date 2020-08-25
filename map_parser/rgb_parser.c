/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:06:35 by deddara           #+#    #+#             */
/*   Updated: 2020/08/25 17:07:32 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

static int	f_check_color_string(char *line, int i, int *rgb)
{
	int				errcode;
	int				number;
	int				comma;

	errcode = 0;
	number = 0;
	comma = 0;
	f_skip_spaces(line, &i);
	while (line[i] && !errcode)
	{
		if (ft_isdigit(line[i]) && number < 3)
		{
			number++;
			rgb[number - 1] = f_cub3d_atoi(line, &i);
			f_skip_spaces(line, &i);
			if (line[i])
				(line[i++] == ',' && comma < 2) ? comma++ : errcode++;
			f_skip_spaces(line, &i);
		}
		else
			errcode++;
	}
	if (errcode || !(number == 3 && comma == 2))
		return (0);
	return (1);
}

int			f_checker(char *line, t_map *map)
{
	int				errcode;
	int				rgb[3];
	int				i;

	i = 0;
	errcode = 0;
	map->count++;
	i++;
	if (!(errcode = f_check_color_string(line, i, rgb)))
		return (0);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (0);
	map->f_rgb = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (1);
}

int			c_checker(char *line, t_map *map)
{
	int				errcode;
	int				rgb[3];
	int				i;

	i = 0;
	errcode = 0;
	map->count++;
	i++;
	if (!(errcode = f_check_color_string(line, i, rgb)))
		return (0);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (0);
	map->c_rgb = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (1);
}

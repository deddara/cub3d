/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 20:53:16 by deddara           #+#    #+#             */
/*   Updated: 2020/08/20 02:01:07 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

static void freesher(char **words)
{
	int i = 0;

	while (i < 2)
	{
		free (words[i]);
		i++;
	}
	free(words);
}

static int word_counter(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i != 2)
		return (0);
	return (1);
}

static int check_is_alone(char *line)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			count++;
		i++;
	}
	if ((line[0] == 'R' || line[0] == 'S' || line[0] == 'C'
		|| line[0] == 'F') && count < 2)
		return (0);
	else if (count < 3)
		return (0);
	return (1);
}

static int r_checker(char *line, t_map *map)
{
	int i;

	i = 0;

	map->count++;
	if(!check_is_alone(line))
		return (0);
	if(!(map->r = ft_split(line, ' ')))
		return (0);
	while(map->r[i])
		i++;
	if (i != 3)
		return(0);
	if (!(check_int(map->r[1]) || !(check_int(map->r[2]))))
		return (0); 
	if(!(map->x = ft_atoi(map->r[1])) || !(map->y = ft_atoi(map->r[2])))
		return (0);
	free (map->r);
	return (1);
}

static int ea_checker(char *line, t_map *map)
{
	char **words;

	map->count++;
	if(!(words = ft_split(line, ' ')))
		return (0);
	if (!(word_counter(words)))
		return (0);
	if (words[1][0] != '.' && words[1][0] != '/')
		return (0);
	if(!(map->ea = ft_strdup(words[1])))
		return (0);
	freesher(words);
	return (1);
}	

static int we_checker(char *line, t_map *map)
{
	char **words;

	map->count++;
	if(!(words = ft_split(line, ' ')))
		return (0);
	if (!(word_counter(words)))
		return (0);
	if (words[1][0] != '.' && words[1][0] != '/')
		return (0);
	if(!(map->we = ft_strdup(words[1])))
		return (0);
	freesher(words);
	return (1);
}	

static int so_checker(char *line, t_map *map)
{
	char **words;

	map->count++;
	if(!(words = ft_split(line, ' ')))
		return (0);
	if (!(word_counter(words)))
		return (0);
	if (words[1][0] != '.' && words[1][0] != '/')
		return (0);
	if(!(map->so = ft_strdup(words[1])))
		return (0);
	freesher(words);
	return (1);
}	

static int no_checker(char *line, t_map *map)
{
	char **words;

	map->count++;
	if(!(words = ft_split(line, ' ')))
		return (0);
	if (!(word_counter(words)))
		return (0);
	if (words[1][0] != '.' && words[1][0] != '/')
		return (0);
	if(!(map->no = ft_strdup(words[1])))
		return (0);
	freesher(words);
	return (1);
}	

static int s_checker(char *line, t_map *map)
{
	char **words;

	map->count++;
	if(!(words = ft_split(line, ' ')))
		return (0);
	if (!(word_counter(words)))
		return (0);
	if (words[1][0] != '.' && words[1][0] != '/')
		return (0);
	if(!(map->s = ft_strdup(words[1])))
		return (0);
	freesher(words);
	return (1);
}

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

static int			f_checker(char *line, t_map *map)
{
	int				errcode;
	int				rgb[3];
	int					i = 0;
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
static int			c_checker(char *line, t_map *map)
{
	int				errcode;
	int				rgb[3];
	int					i = 0;
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

int		check_elems(char *line, t_map *map)
{
	if (line[0] == 'R')
		return(((r_checker(line, map))));
	else if (line[0] == 'N' && line[1] == 'O')
		return((no_checker(line, map)));
	else if (line[0] == 'S' && line[1] == 'O')
		return((so_checker(line, map)));
	else if (line[0] == 'W' && line[1] == 'E')
		return(((we_checker(line, map))));
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

static int check_all_params(t_map *map)
{
	if (map->x == 0 || map->y == 0 || map->count != 8 || map->no == NULL || 
	map->so == NULL || map->we == NULL || map->ea == NULL || map->s == NULL
	|| map->f_rgb == (unsigned long)-1 || map->c_rgb == (unsigned long)-1)
		return (0);
	return (1);
}

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
	while(get_next_line(fd, &line))
	{		
		if(line[0] == '\0')
		{	
			free(line);
			continue ;
		}
		if(!(check_elems(line, map)))
			return (error_handler(map, line, 3));
		if(map->count == 8)
			break ;
		free(line);
	}
	free (line);
	if(!(check_all_params(map)))
		return (error_handler(map, line, 3));
	get_next_line(fd, &line);
	if ((line[0] == ' ' || line[0] == '1'))
		return (error_handler(map, 0, 5));
	free (line);
	while(get_next_line(fd, &line))
	{
		if(line[0] == '\0' && map->y_count == 0)
		{	
			free (line);
			continue;
		}
		else if ((line && line[0] != ' ' && line[0] != '1')&& map->y_count != 0)
			return (error_handler(map, line, 4));
		if(!(map_line_parser(line, map)))
			return (error_handler(map, line, 4));
		free(line);
	}
	if ((line && line[0] != ' ' && line[0] != '1')&& map->y_count != 0)
		return (error_handler(map, line, 4));	
	if(!(map_line_parser(line, map)))
		return (error_handler(map, line, 4));
	free (line);
	if(!(map_parser(map)))
		return (error_handler(map, 0, 5));
	if(!get_angle(map))
		return(0);
	longest_width(map);
	return (1);
}
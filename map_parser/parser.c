/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 20:53:16 by deddara           #+#    #+#             */
/*   Updated: 2020/08/02 12:11:20 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

static unsigned long create_rgb(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
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

static int f_word_counter(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i != 3)
		return (0);
	return (1);
}

static int r_checker(char *line, t_map *map)
{
	int i;

	i = 0;

	map->count++;
	if(!(map->r = ft_split(line, ' ')))
		return (0);
	if (!(check_int(map->r[1]) || !(check_int(map->r[2]))))
		return (0); 
	if(!(map->x = ft_atoi(map->r[1])) || !(map->y = ft_atoi(map->r[2])))
		return (0);
	while(map->r[i])
		i++;
	if (i != 3)
		return(0);
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
	free (*words);
	free (words);
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
	free (*words);
	free (words);
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
	free (*words);
	free (words);
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
	
	free (*words);
	free (words);
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
	free (*words);
	free (words);
	return (1);
}

int		f_checker(char *line, t_map *map)
{
	char	**words;
	char	**nums;
	int		r;
	int 	g;
	int		b;

	map->count++;
	if (!(words = ft_split(line, ' ')))
		return (0);
	if (!(word_counter(words)))
		return (0);
	if (!(nums = ft_split(words[1], ',')))
		return (0);
	if (!(f_word_counter(nums)) || !(check_int(nums[0]) || !(check_int(nums[1]))) || !(check_int(nums[2])))
		return (0);
	r = ft_atoi(nums[0]);
	g = ft_atoi(nums[1]);
	b = ft_atoi(nums[2]);
	if (line[0] == 'F')
		map->f_rgb = create_rgb(r, g, b);
	else
		map->c_rgb = create_rgb(r, g ,b);
	free (*words);
	free (words);
	free (*nums);
	free (nums);
	return (1);
}

int		check_elems(char *line, t_map *map)
{
	int i;

	i = 0;
	if (line[0] == 'R')
		if (!(r_checker(line, map)))
			return (0);
	if (line[0] == 'N' && line[1] == 'O')
		if (!(no_checker(line, map)))
			return (0);
	if (line[0] == 'S' && line[1] == 'O')
		if (!(so_checker(line, map)))
			return (0);	
	if (line[0] == 'W' && line[1] == 'E')
		if (!(we_checker(line, map)))
			return (0);	
	if (line[0] == 'E' && line[1] == 'A')
		if (!(ea_checker(line, map)))
			return (0);	
	if (line[0] == 'S' && line[1] == ' ')
		if (!(s_checker(line, map)))
			return (0);
	if (line[0] == 'F' && line[1] == ' ')
		if (!(f_checker(line, map)))
			return (0);
	if (line[0] == 'C' && line[1] == ' ')
		if (!(f_checker(line, map)))
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


int		parser(t_map *map)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("/Users/deddara/school21/cub3d/cub3d_github/example_map.cub", O_RDONLY);
	if(!ft_lstmapnew(map))
		return(0);

	while(get_next_line(fd, &line))
	{
		
		if(line[0] == '\0')
			continue ;
		if(!(check_elems(line, map)))
		{
			printf("===ERROR===\n");
			return (0);
		}
		printf("%s\n", line);
		if(map->count == 8)
			break ;
		free(line);
	}
	free (line);
	if(!(check_all_params(map)))
	{
		printf("===ERROR===\n");
		return (0);	
	}
	//MAP PARSING PART
	// printf ("\n=== MAP TIME ===\n\n");

	while(get_next_line(fd, &line))
	{
		if(line[0] == '\0' && map->y_count == 0)
			continue ;
		else if (line[0] == '\0' && map->y_count != 0)
			return (0);
		if(!(map_line_parser(line, map)))
		{	
			printf("===ERROR===\n");
			return (0);
		}
		printf("%s\n", line);
		free(line);
	}
	//добавить проверку на отсутствие игрока!
	if(!(map_line_parser(line, map)))
	{	
		printf("===ERROR===\n");
		return (0);
	}
	if(!(map_parser(map)))
	{	
		printf("===ERROR===\n");
		return (0);
	}
	printf("== %d ==\n", map->x);
	free(line);
	return (1);
}
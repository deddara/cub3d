/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 20:53:16 by deddara           #+#    #+#             */
/*   Updated: 2020/07/28 18:56:29 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

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
	words = ft_split(line, ' ');
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
	words = ft_split(line, ' ');
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
	words = ft_split(line, ' ');
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
	words = ft_split(line, ' ');
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
	words = ft_split(line, ' ');
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
	if (line[0] == 'S' && line[1] != 'O')
		if (!(s_checker(line, map)))
			return (0);	
	return (1);
}

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
		if(line[0] == '\0')
			continue ;
		if(!(check_elems(line, map)))
		{	
			printf("===ERROR===\n");
			return (0);
		}
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free (line);
	return (0);
}
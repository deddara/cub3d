#include "map_parser.h"

int ea_checker(char *line, t_map *map)
{
	char **words;

	words = NULL;
	map->count++;
	if(!(words = ft_split(line, ' ')) || !(word_counter(words)) || (words[1][0] != '.' && words[1][0] != '/')
		|| !(map->ea = ft_strdup(words[1])))
	{
		freesher(words);
		return (0);
	}
	freesher(words);
	return (1);
}	

int we_checker(char *line, t_map *map)
{
	char **words;

	words = NULL;
	map->count++;
	if(!(words = ft_split(line, ' ')) || !(word_counter(words)) || (words[1][0] != '.' && words[1][0] != '/')\
		|| !(map->we = ft_strdup(words[1])))
	{
		freesher(words);
		return (0);
	}
	freesher(words);
	return (1);
}	

int so_checker(char *line, t_map *map)
{
	char **words;

	words = NULL;
	map->count++;
	if(!(words = ft_split(line, ' ')) || !(word_counter(words)) || (words[1][0] != '.' && words[1][0] != '/')\
		|| !(map->so = ft_strdup(words[1])))
	{
		freesher(words);
		return (0);
	}
	freesher(words);
	return (1);
}	

int no_checker(char *line, t_map *map)
{
	char **words;

	words = NULL;
	map->count++;
	if(!(words = ft_split(line, ' ')) || !(word_counter(words)) || (words[1][0] != '.' && words[1][0] != '/')\
		|| !(map->no = ft_strdup(words[1])))
	{
		freesher(words);
		return (0);
	}
	freesher(words);
	return (1);
}	

int s_checker(char *line, t_map *map)
{
	char **words;

	words = NULL;
	map->count++;
	if(!(words = ft_split(line, ' ')) || !(word_counter(words)) || (words[1][0] != '.' && words[1][0] != '/')\
		|| !(map->s = ft_strdup(words[1])))
	{
		freesher(words);
		return (0);
	}
	freesher(words);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 20:53:11 by deddara           #+#    #+#             */
/*   Updated: 2020/07/29 04:15:08 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H

# include "main.h"

typedef struct		s_map
{
	char	**r;
	int		x;
	int		y;
	int		count;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	unsigned long f_rgb;
	unsigned long c_rgb;
	char 	**map;
	char	player_pos;
	char	*map_line;
	int		y_count;
}					t_map;

t_map				*ft_lstmapnew();
int					parser(t_map *map);
int					check_elems(char *line, t_map *map);
int 				check_int(char *str);
int 				map_line_parser(char *line, t_map *map);
int					map_parser(t_map *map);
int					first_last(char *line, t_map *map);
#endif

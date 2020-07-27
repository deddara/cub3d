/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 20:53:11 by deddara           #+#    #+#             */
/*   Updated: 2020/07/27 22:51:13 by deddara          ###   ########.fr       */
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
	char	*c;
	int		f_rgb[2];
	int		c_rgb[2];
}					t_map;

t_map				*ft_lstmapnew();
int					map_parser(t_map *map);
int					check_elems(char *line, t_map *map);
#endif

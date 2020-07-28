/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:41:07 by deddara           #+#    #+#             */
/*   Updated: 2020/07/29 02:21:12 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

t_map	*ft_lstmapnew()
{
	t_map *var;

	var = malloc(sizeof(t_map));
	if (!var)
		return (0);
    var->count = 0;
	var->x = 0;
	var->y = 0; 
    var->no = NULL;
    var->so = NULL;
    var->we = NULL;
    var->ea = NULL;
    var->s = NULL;
    var->c_rgb = -1;
	var->f_rgb = -1;
	var->y_count = 0;
	if(!(var->map_line = (char*)malloc(sizeof(char) * 1)))
		return (NULL);
	var->map_line[0] = '\0';
    var->no = NULL;
	return (var);
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
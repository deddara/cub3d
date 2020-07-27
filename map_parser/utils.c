/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:41:07 by deddara           #+#    #+#             */
/*   Updated: 2020/07/27 21:59:21 by deddara          ###   ########.fr       */
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
    var->no = NULL;
    var->so = NULL;
    var->we = NULL;
    var->ea = NULL;
    var->s = NULL;
    var->c = NULL;
    var->no = NULL;
	return (var);
}
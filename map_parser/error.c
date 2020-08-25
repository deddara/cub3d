/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 21:34:44 by deddara           #+#    #+#             */
/*   Updated: 2020/08/25 13:52:46 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

int		error_handler(t_map *map,char *line, int code)
{
	map = NULL;
	if (code == 1)
		ft_putstr_fd("==INVALID FILE==", 0);
	else if (code == 2)
		ft_putstr_fd("==MALLOC ERROR==", 0);
	else if (code == 3)
	{	
		ft_putstr_fd("==PARAMS ERROR==\n--->", 0);
		ft_putstr_fd(line, 0);
	}
	else if (code == 4)
	{	
		ft_putstr_fd("==MAP ERROR==\n--->", 0);
	}
	else if (code == 5)
	{	
		ft_putstr_fd("==MAP ERROR==\n--->", 0);
	}
	return (0);
}
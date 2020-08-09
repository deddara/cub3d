/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 14:47:52 by deddara           #+#    #+#             */
/*   Updated: 2020/08/09 14:54:57 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# define ANGLE 66

#include "main.h"

typedef struct s_raycast
{
	double	camera_x;
	int		dir_x;
	int		dir_y;
	int		ray_dir_x;
	int		ray_dir_y;
	double	player_x;
	double	player_y;
	int		map_x;
	int		map_y;
}				t_raycast;

void	ray_caster(t_map *map, t_data *img);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:22:20 by deddara           #+#    #+#             */
/*   Updated: 2020/08/02 12:13:31 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}



int             main(void)
{
    t_data  img;
    t_vars vars;
    t_map map;
    // int x;
    // int y;
    int i;

	i = 3;
	parser(&map);
    // x = 5;
    // y = 5;
	printf("== %d ==", map.x);
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, map.x, map.y, "Hello world!");
    img.img = mlx_new_image(vars.mlx, map.x, map.y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    
    mlx_loop(vars.mlx);
	return (0);
}
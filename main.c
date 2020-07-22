/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:49:46 by deddara           #+#    #+#             */
/*   Updated: 2020/07/22 19:41:14 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include <stdio.h>
int main()
{
    void    *mlx_ptr;
    void    *window;
    int x, y;

    x = 500;
    y = 500;
    mlx_ptr = mlx_init();
    window = mlx_new_window(mlx_ptr, 1920, 1080, "mlx42");
    while(x < 700)
    {
        mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
        x++;
        y++;
    }
    y = 500;
    while(x > 500)
    {
        mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
        x--;
        y++;
    }
    y = 500;
    x = 720;
    while(x < 820)
    {
        mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
        x++;
        y++;
    }
    while(x > 720)
    {
        mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
        x--;
        y++;
    }
    while(x < 920)
    {
        mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
        x++;
        y--;
    }
    x = 960;
    y = 500;
    mlx_pixel_put(mlx_ptr, window, x, y, 0x0000ff);
    while(y < 700)
    {
        mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
        y++;
    }
    while(y > 500)
    {
        mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
        y--;
        x++;
    }
    y = 500;
    mlx_pixel_put(mlx_ptr, window, x, y, 0x0000ff);
    while(y < 700)
    {
        mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
        y++;
    }
    y = 460;
    x -= 120;
    while(x < 1090)
    {
        mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
        x++;
    }
    mlx_loop(mlx_ptr);
}
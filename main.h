/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:22:15 by deddara           #+#    #+#             */
/*   Updated: 2020/07/24 22:01:46 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "./libft/libft.h"
# include "./minilibx/mlx.h"
# include "./map_parser/map_parser.h"
# include <stdlib.h>
# include <unistd.h>
typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;


typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

#endif
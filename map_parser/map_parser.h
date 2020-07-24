/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 20:53:11 by deddara           #+#    #+#             */
/*   Updated: 2020/07/24 21:22:07 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

typedef struct s_map
{
    int     x;
    int     y;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    
    char    *s;
    int     f_rgb[2];
    int     c_rgb[2];
    char    *c;
}               t_map;
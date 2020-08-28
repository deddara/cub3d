/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_scr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:05:28 by deddara           #+#    #+#             */
/*   Updated: 2020/08/28 16:48:53 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int		make_header(char *bmp_fheader, char *bmpinfheader,\
t_raycast *ray, t_data *img)
{
	int file_size;

	file_size = 14 + 40 + ray->map->x * ray->map->y * \
			img->bits_per_pixel / 8;
	bmp_fheader[0] = 'B';
	bmp_fheader[1] = 'M';
	bmp_fheader[2] = (char)(file_size);
	bmp_fheader[3] = (char)(file_size >> 8);
	bmp_fheader[4] = (char)(file_size >> 16);
	bmp_fheader[5] = (char)(file_size >> 24);
	bmp_fheader[10] = (char)(14 + 40);
	bmpinfheader[0] = (char)(40);
	bmpinfheader[4] = (char)(ray->map->x);
	bmpinfheader[5] = (char)(ray->map->x >> 8);
	bmpinfheader[6] = (char)(ray->map->x >> 16);
	bmpinfheader[7] = (char)(ray->map->x >> 24);
	bmpinfheader[8] = (char)(-ray->map->y);
	bmpinfheader[9] = (char)(-ray->map->y >> 8);
	bmpinfheader[10] = (char)(-ray->map->y >> 16);
	bmpinfheader[11] = (char)(-ray->map->y >> 24);
	bmpinfheader[12] = (char)(1);
	bmpinfheader[14] = (char)(img->bits_per_pixel);
	return (1);
}

static int		write_in_header(char *bmp_fheader, char *bmpinfheader,\
t_raycast *ray, t_data *img)
{
	int		fd;
	char	*fname;

	fname = "screenshot.bmp";
	if ((fd = open(fname, O_RDWR | O_CREAT, 777)) < 0)
		return (0);
	write(fd, bmp_fheader, 14);
	write(fd, bmpinfheader, 40);
	write(fd, img->addr, ray->map->x * ray->map->y * \
			img->bits_per_pixel / 8);
	if (close(fd < 0))
	{
		ft_putstr_fd("close error", 0);
		return (0);
	}
	return (1);
}

int				make_scr(t_raycast *ray, t_data *img)
{
	char bmp_fheader[14];
	char bmpinfheader[40];

	ft_bzero(bmp_fheader, 14);
	ft_bzero(bmpinfheader, 40);
	make_header(bmp_fheader, bmpinfheader, ray, img);
	if (!(write_in_header(bmp_fheader, bmpinfheader, ray, img)))
		ft_putstr_fd("scr error\n", 0);
	close(0);
	return (0);
}

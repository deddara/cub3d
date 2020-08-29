/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_scr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:05:28 by deddara           #+#    #+#             */
/*   Updated: 2020/08/29 20:02:54 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int		make_header(unsigned char *bmp_fheader, \
unsigned char *bmpinfheader, t_raycast *ray, t_data *img)
{
	int file_size;

	file_size = 14 + 40 + ray->map->x * ray->map->y * \
			img->bits_per_pixel / 8;
	bmp_fheader[0] = 'B';
	bmp_fheader[1] = 'M';
	bmp_fheader[2] = (unsigned char)(file_size);
	bmp_fheader[3] = (unsigned char)(file_size >> 8);
	bmp_fheader[4] = (unsigned char)(file_size >> 16);
	bmp_fheader[5] = (unsigned char)(file_size >> 24);
	bmp_fheader[10] = (unsigned char)(14 + 40);
	bmpinfheader[0] = (unsigned char)(40);
	bmpinfheader[4] = (unsigned char)(ray->map->x);
	bmpinfheader[5] = (unsigned char)(ray->map->x >> 8);
	bmpinfheader[6] = (unsigned char)(ray->map->x >> 16);
	bmpinfheader[7] = (unsigned char)(ray->map->x >> 24);
	bmpinfheader[8] = (unsigned char)(-ray->map->y);
	bmpinfheader[9] = (unsigned char)(-ray->map->y >> 8);
	bmpinfheader[10] = (unsigned char)(-ray->map->y >> 16);
	bmpinfheader[11] = (unsigned char)(-ray->map->y >> 24);
	bmpinfheader[12] = (unsigned char)(1);
	bmpinfheader[14] = (unsigned char)(img->bits_per_pixel);
	return (1);
}

static int		write_in_header(unsigned char *bmp_fheader,\
unsigned char *bmpinfheader, t_raycast *ray, t_data *img)
{
	int		fd;
	char	*fname;
	int		line_len;
	int		i;

	i = 0;
	fname = "screenshot.bmp";
	if ((fd = open(fname, O_RDWR | O_CREAT, 0755)) < 0)
		return (0);
	write(fd, bmp_fheader, 14);
	write(fd, bmpinfheader, 40);
	line_len = img->bits_per_pixel / 8 * ray->map->x;
	while (i < ray->map->y)
	{
		write(fd, img->addr + i * img->line_length, line_len);
		i++;
	}
	if (close(fd < 0))
	{
		ft_putstr_fd("close error", 0);
		return (0);
	}
	return (1);
}

int				make_scr(t_raycast *ray, t_data *img)
{
	unsigned char bmp_fheader[14];
	unsigned char bmpinfheader[40];

	ft_bzero(bmp_fheader, 14);
	ft_bzero(bmpinfheader, 40);
	make_header(bmp_fheader, bmpinfheader, ray, img);
	if (!(write_in_header(bmp_fheader, bmpinfheader, ray, img)))
		ft_putstr_fd("scr error\n", 0);
	close(0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:19:45 by deddara           #+#    #+#             */
/*   Updated: 2020/08/13 23:19:05 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"


static void	list_swap(t_sprite *tmp, t_sprite *a)
{
	int		t;
	double	j;
	t = 0;
	t = tmp->id;
	tmp->id = a->id;
	a->id = t;
	j = tmp->x;
	tmp->x = a->x;
	a->x = j;
	j = tmp->y;
	tmp->y = a->y;
	a->y = j;
	j = tmp->dist;
	tmp->dist = a->dist;
	a->dist = j;
}

void sprites_sort(t_raycast *ray)
{
 	t_sprite *tmp;
    t_sprite *a;
    int flag=1;
    while(flag==1)
    {
        tmp=ray->sprite;
        a=tmp->next;
        flag=0;
        while(a)
        {
            if((tmp->dist)<(a->dist))
            {
				list_swap(tmp, a);
                flag=1;
            }
            tmp=tmp->next;
            a=a->next;
        }
    }
}

static t_sprite	*new_sprite(int y, int x)
{
	t_sprite *sprite;

	if (!(sprite = malloc(sizeof(t_sprite) * 1)))
		return NULL;
	sprite->y = y;
	sprite->x = x;
	sprite->id = 0;
	sprite->prev = NULL;
	sprite->next = NULL;
	return (sprite);
}

static void add_sprite(t_sprite *sprite, int y, int x, int id)
{
	t_sprite *tmp;
	t_sprite *new;

	if (!(new = malloc(sizeof(t_sprite) * 1)))
		return ;
	new->y = y;
	new->x = x;
	new->id = id;
	new->dist = 0;
	tmp = sprite;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
}

void		sprites_count(t_raycast *ray, t_map *map)
{
	int			i;
	int			j;
	int			flag;
	t_sprite	*sprite;

	flag = 0;
	i = 1;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '2' && flag == 0)
			{
				sprite = new_sprite(i , j);
				flag++;
			}
			else if (map->map[i][j] == '2' && flag)
			{
				add_sprite(sprite, i, j, flag);
				flag++;
			}
			j++;
		}
		i++;
	}
	ray->sprite = sprite;
}

static void sprite_dist_calc(t_raycast *ray)
{
	t_sprite	*sp;

	sp = ray->sprite;
	while (sp)
	{
		sp->dist = sqrt(pow(ray->player_x - sp->x, 2) + \
						pow(ray->player_y - sp->y, 2));
		sp = sp->next;
	}
}

void	sprite_handler(t_raycast *ray)
{	
	int color;
	t_sprite *tmp;
	sprite_dist_calc(ray);
	sprites_sort(ray);
	tmp = ray->sprite;
	while (tmp->next)
    {
      double spriteX = tmp->x - ray->player_x;
      double spriteY = tmp->y - ray->player_y;
      double invDet = 1.0 / (ray->plane_x * ray->dir_y - ray->dir_x * ray->plane_y); //required for correct matrix multiplication
      double transformX = invDet * (ray->dir_y * spriteX - ray->dir_x * spriteY);
      double transformY = invDet * (-ray->plane_y * spriteX + ray->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
      int spriteScreenX = (int)((ray->map->x / 2) * (1 + transformX / transformY));
      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY);
      int spriteHeight = abs((int)(ray->map->y / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
      int drawStartY = -spriteHeight / 2 +ray->map->y / 2 + vMoveScreen;
      if(drawStartY < 0)
	  	drawStartY = 0;
      int drawEndY = spriteHeight / 2 +ray->map->y / 2 + vMoveScreen;
      if(drawEndY >=ray->map->y) 
	  	drawEndY =ray->map->y - 1;
      int spriteWidth = abs( (int) (ray->map->y / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) 
	  	drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= ray->map->x) 
	  	drawEndX = ray->map->x - 1;
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * ray->txtr_s.width / spriteWidth) / 256;
        if(transformY > 0 && stripe > 0 && stripe < ray->map->x && transformY < ray->x_buffer[stripe])
		{
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        	{
        	  	int d = (y-vMoveScreen) * 256 -ray->map->y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
     	     	int texY = ((d * ray->txtr_s.height) / spriteHeight) / 256;
	
			 	color = getpixelcolor(ray->txtr_ea.img, texX, texY); //get current color from the texture
					my_mlx_pixel_put(ray->img,  stripe, y, color); //paint pixel if it isn't black, black is the invisible color
        	}
	  }
	  }
	tmp = tmp->next;
}
}
#include <mlx.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int x;
    int y;

    x = 5;
    y = 5;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

    while (x < 700)
    {
        y = 5;
        while (y < 60)
        {
            my_mlx_pixel_put(&img, x, y, 0xFF0018);
            y++;
        }
        x++;
    }
    x = 5;
     while (x < 700)
    {
        y = 60;
        while (y < 120)
        {
            my_mlx_pixel_put(&img, x, y, 0xFFA52C);
            y++;
        }
        x++;
    }
    x = 5;
     while (x < 700)
    {
        y = 120;
        while (y < 180)
        {
            my_mlx_pixel_put(&img, x, y, 0xFFFF41);
            y++;
        }
        x++;
    }
    x = 5;
     while (x < 700)
    {
        y = 180;
        while (y < 240)
        {
            my_mlx_pixel_put(&img, x, y, 0x008018);
            y++;
        }
        x++;
    }
    x = 5;
     while (x < 700)
    {
        y = 240;
        while (y < 300)
        {
            my_mlx_pixel_put(&img, x, y, 0x0000F9);
            y++;
        }
        x++;
    }
     x = 5;
     while (x < 700)
    {
        y = 300;
        while (y < 360)
        {
            my_mlx_pixel_put(&img, x, y, 0x86007D);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
#include "execution.h"
#include "cub3d.h"

int rgb_to_hex(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

void ft_init_cub3d(t_execution *cub3d, t_src *src)
{
    cub3d->map = src->map->grid;
    cub3d->floor_color = rgb_to_hex(src->colors.floor_r, 
                                    src->colors.floor_g, 
                                    src->colors.floor_b);
    cub3d->ceiling_color = rgb_to_hex(src->colors.ceiling_r, 
                                      src->colors.ceiling_g, 
                                      src->colors.ceiling_b);
    cub3d->mlx = mlx_init();
    if (!cub3d->mlx)
        exit_failure("Error initializing MLX");
    cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");
    if (!cub3d->win)
        exit_failure("Error creating window");
    cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
    if (!cub3d->img)
        exit_failure("Error creating image");
    cub3d->pixels_ptr = mlx_get_data_addr(cub3d->img, &cub3d->bits_per_pixel, 
                                          &cub3d->line_length, &cub3d->endian);
    if (!cub3d->pixels_ptr)
        exit_failure("Error getting image data address");
    mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}
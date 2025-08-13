#include "execution.h"
#include "cub3d.h"

void	my_mlx_pixel_put(int x, int y, t_execution *execution, int color)
{
	char	*dst;
	
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return;
	dst = execution->pixels_ptr + (y * execution->line_length + x * (execution->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_square(int x, int y, t_execution *execution, int size, int color)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            my_mlx_pixel_put(x + j, y + i, execution, color);
        }
    }
}

void init_cub3d(t_execution *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
			exit_failure("Error initializing MLX");
	cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!cub3d->win)
		exit_failure("Error creating window");
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img)
		exit_failure("Error creating image");
	cub3d->pixels_ptr = mlx_get_data_addr(cub3d->img, &cub3d->bits_per_pixel, &cub3d->line_length, &cub3d->endian);
	if (!cub3d->pixels_ptr)
		exit_failure("Error getting image data address");
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}

int draw_a_loop(t_execution *execution)
{
	t_player *player = &execution->player;
	player_movement(player); // Update player position based on key presses
	draw_square(player->x, player->y, execution, 5, 0x00FF00); // Draw player as a green square
	mlx_put_image_to_window(execution->mlx, execution->win, execution->img, 0, 0);
	return (0);
}
void execution(t_src *src)
{
	(void)src; // src is not used in this function, but can be used for future enhancements
	t_execution cub3d;

	init_cub3d(&cub3d);

	mlx_hook(cub3d.win, 2, 1L<<0, key_press, &cub3d.player);
	mlx_hook(cub3d.win, 3, 1L<<1, key_release, &cub3d.player);	
	mlx_loop_hook(cub3d.mlx, draw_a_loop, &cub3d.player);
	mlx_loop(cub3d.mlx);
}
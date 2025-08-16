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

	i = 0;
	j = 0;
    while (i < size)
    {
		j = 0;
        while(j < size)
        {
            my_mlx_pixel_put(x + j, y + i, execution, color);
			j++;
		}
		i++;
    }
}

void init_cub3d(t_execution *cub3d, t_src *src)
{
	cub3d->map = src->map->grid;
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

void draw_map(t_execution *execution)
{
	char **map;
	int color;

	map = execution->map;
	color = 0xFFFFFF; // Default color for the map
	for (int y = 0; map[y]; y++)
	{
		for (int x = 0; map[y][x]; x++)
		{
			if (map[y][x] == '1') // Wall
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, execution, BLOCK_SIZE, color); // White for walls
			// else if (map[y][x] == '0') // Empty space
			// 	color = 0x000000; // Black for empty spaces
			// else if (map[y][x] == 'P') // Player position
			// 	color = 0x00FF00; // Green for player

			// my_mlx_pixel_put(x, y, execution, color);
		}
	}
	// mlx_put_image_to_window(execution->mlx, execution->win, execution->img, 0, 0);
}
void clear_image(t_execution *execution)
{
	int i;

	// Clear the image buffer
	for (i = 0; i < WIDTH * HEIGHT; i++)
		((int *)execution->pixels_ptr)[i] = 0x000000; // Set all pixels to black
}

bool touch(float px, float py,t_execution *execution)
{
	int x = (px / BLOCK_SIZE);
	int y = (py / BLOCK_SIZE);

	if (execution->map[y][x] == '1') // Assuming '1' represents a wall
		return true; // Touching a wall

	return false; // Not touching a wall
}
int draw_a_loop(t_execution *execution)
{

	clear_image(execution);		
	t_player *player = &execution->player;
	player_movement(player);
	draw_square(player->x, player->y, execution, PLAYER_SIZE, 0x00FF00);
	draw_map(execution);

	float ray_x = player->x;
	float ray_y = player->y;
	float ray_sin_angle = sin(player->angle);
	float ray_cos_angle = cos(player->angle);

	while (!touch(ray_x, ray_y, execution))
	{
		my_mlx_pixel_put(ray_x, ray_y, execution, 0xFF0000); // Draw the ray in red
		ray_x += ray_cos_angle;
		ray_y -= ray_sin_angle; // Subtract because y-axis is inverted in most graphics libraries
	}
	mlx_put_image_to_window(execution->mlx, execution->win, execution->img, 0, 0);
	return (0);
}

void execution(t_src *src)
{
	t_execution cub3d;

	init_cub3d(&cub3d, src);
	init_player(&cub3d.player); // Initialize player position and keys

	mlx_hook(cub3d.win, 2, 1L<<0, key_press, &cub3d.player);
	mlx_hook(cub3d.win, 3, 1L<<1, key_release, &cub3d.player);	
	mlx_loop_hook(cub3d.mlx, draw_a_loop, &cub3d);
	mlx_loop(cub3d.mlx);
}
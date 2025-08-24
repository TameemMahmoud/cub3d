#include "execution.h"
#include "cub3d.h"

void clear_image(t_execution *execution)
{
    int i;
    
    for (i = 0; i < (WIDTH * HEIGHT); i++)
        ((int *)execution->pixels_ptr)[i] = 0x000000; // Black
}

bool touch(float px, float py, t_execution *execution)
{
    int x = (int)(px / BLOCK_SIZE);
    int y = (int)(py / BLOCK_SIZE);

    // Bounds checking to prevent segfault
    if (y < 0 || x < 0)
        return true;
    
    if (!execution->map || !execution->map[y])
        return true;
    
    if (execution->map[y][x] == '\0')
        return true;

    // Wall character
    if (execution->map[y][x] == '1')
        return true;
    
    // All other characters (0, N, S, E, W) are walkable
    return false;
}

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

void execution(t_src *src)
{
	t_execution cub3d;

	ft_init_cub3d(&cub3d, src);
    ft_init_player(&cub3d.player, src);
	mlx_hook(cub3d.win, 2, 1L<<0, key_press, &cub3d.player);
	mlx_hook(cub3d.win, 3, 1L<<1, key_release, &cub3d.player);	
	mlx_loop_hook(cub3d.mlx, draw_a_loop, &cub3d);
	mlx_loop(cub3d.mlx);
}
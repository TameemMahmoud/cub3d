#include "execution.h"
#include "cub3d.h"

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

void draw_map(t_execution *execution)
{
    char **map;
    int color;
    int y;
	int x;
	
	x = 0;
	y = 0;
    map = execution->map;
    color = 0xFF0000; // Red color for walls

    while (map[y] != NULL)
    {
        x = 0;
        while (map[y][x] != '\0')
        {
            if (map[y][x] == '1')
                draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, execution, BLOCK_SIZE, color);
            x++;
        }
        y++;
    }
}

int draw_a_loop(t_execution *execution)
{
	float fraction;
	float start_x;
	int i;

	fraction = PI / 3 / WIDTH;
	i = 0;
	clear_image(execution);		
	t_player *player = &execution->player;
	player_movement(player);
	start_x = player->angle - (PI / 6);
	// draw_square(player->x, player->y, execution, PLAYER_SIZE, 0x00FF00);
	// draw_map(execution);

	while(i < WIDTH)
	{
		draw_line(player, execution, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(execution->mlx, execution->win, execution->img, 0, 0);
	return (0);
}

void draw_line(t_player *player, t_execution *execution, float x, int i)
{
    float cos_angle = cos(x);
    float sin_angle = sin(x);
    float ray_x = player->x;
    float ray_y = player->y;
    
    while(!touch(ray_x, ray_y, execution))
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
        
        // Safety check to prevent infinite loops
        if (ray_x < 0 || ray_y < 0 || ray_x >= WIDTH || ray_y >= HEIGHT)
            break;
    }
    
    float dist = distance(ray_x - player->x, ray_y - player->y);
    if (dist < 0.1) dist = 0.1;
    
    float height = (BLOCK_SIZE / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - height) / 2;
    int end_y = start_y + height;
    
    // Ensure we don't draw outside screen bounds
    if (start_y < 0) start_y = 0;
    if (end_y >= HEIGHT) end_y = HEIGHT - 1;
    
    // Only draw the wall portion (between start_y and end_y)
    while(start_y < end_y)
    {
        my_mlx_pixel_put(i, start_y, execution, 0x8B4513); // Brown wall color
        start_y++;
    }
    // Note: We don't draw anything for ceiling and floor areas
    // They're already drawn in clear_image()
}
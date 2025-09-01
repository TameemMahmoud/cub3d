#include "execution.h"
#include "cub3d.h"

float fixed_dist(float x1, float y1, float x2, float y2, t_execution *game)
{
    float delta_x;
    float delta_y;
    float angle;
    float fix_dist;
    
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    angle = atan2(delta_y, delta_x) - game->player.angle;
    fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
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
void draw_line(t_player *player, t_execution *execution, float x, int i)
{
    float cos_angle;
    float sin_angle;
    float ray_x;
    float ray_y;
    
    cos_angle = cos(x);
    sin_angle = sin(x);
    ray_x = player->x;
    ray_y = player->y;
    
    // Cast ray until it hits a wall
    while(!touch(ray_x, ray_y, execution))
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
        
        // Prevent infinite loops
        if (ray_x < 0 || ray_y < 0 || ray_x >= WIDTH || ray_y >= HEIGHT)
            break;
    }
    
    // Calculate distance
    float dist = fixed_dist(player->x, player->y, ray_x, ray_y, execution);
    if (dist < 1) 
        dist = 1;
    
    float height = (BLOCK_SIZE / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;
    
    // Draw white wall line
    while(start_y < end)
    {
        my_mlx_pixel_put(i, start_y, execution, 0xFFFFFF); // White
        start_y++;
    }
}


int draw_a_loop(t_execution *execution)
{
	float fraction;
	float start_x;
	int i;

	t_player *player = &execution->player;
	clear_image(execution);		
	ft_player_movement(player, execution);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
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


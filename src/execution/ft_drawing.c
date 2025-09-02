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
void draw_ceiling_floor(t_execution *execution, int column, int wall_start, int wall_end)
{
	int y;
	
	y = 0;
	while (y < wall_start)
	{
		my_mlx_pixel_put(column, y, execution, execution->ceiling_color);
		y++;
	}
	y = wall_end;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(column, y, execution, execution->floor_color);
		y++;
	}
}

void draw_wall_column(t_execution *execution, int column, int wall_start, int wall_end)
{
	int y;
	
	y = wall_start;
	while (y < wall_end && y < HEIGHT)
	{
		my_mlx_pixel_put(column, y, execution, 0xFFFFFF);
		y++;
	}
}

void cast_ray(t_player *player, t_execution *execution, float angle, float *ray_x, float *ray_y)
{
	float cos_angle;
	float sin_angle;
	
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	*ray_x = player->x;
	*ray_y = player->y;
	
	while (!touch(*ray_x, *ray_y, execution))
	{
		*ray_x += cos_angle;
		*ray_y += sin_angle;
		if (*ray_x < 0 || *ray_y < 0 || *ray_x >= WIDTH || *ray_y >= HEIGHT)
			break;
	}
}

void draw_line(t_player *player, t_execution *execution, float x, int i)
{
	float ray_x;
	float ray_y;
	float dist;
	float height;
	int wall_start;
	int wall_end;
	
	cast_ray(player, execution, x, &ray_x, &ray_y);
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, execution);
	if (dist < 1)
		dist = 1;
	height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	wall_start = (HEIGHT - height) / 2;
	wall_end = wall_start + height;
	draw_ceiling_floor(execution, i, wall_start, wall_end);
	draw_wall_column(execution, i, wall_start, wall_end);
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


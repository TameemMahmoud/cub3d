#include "cub3d.h"
#include "execution.h"

float	fixed_dist(float x1, float y1, float x2, float y2, t_execution *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;
}


int find_closest_wall_face(float *distances)
{
	float	min_dist;
	int		direction;
	int		i;

	min_dist = distances[0];
	direction = 0;
	i = 1;
	while (i < 4)
	{
		if (distances[i] < min_dist)
		{
			min_dist = distances[i];
			direction = i;
		}
		i++;
	}
	return direction;
}

int get_wall_direction(float ray_x, float ray_y)
{
	int		map_x;
	int		map_y;
	float	block_x;
	float	block_y;
	float	distances[4];

	map_x = (int)(ray_x / BLOCK_SIZE);
	map_y = (int)(ray_y / BLOCK_SIZE);
	block_x = (ray_x / BLOCK_SIZE) - map_x;
	block_y = (ray_y / BLOCK_SIZE) - map_y;
    distances[0] = block_y;            // Distance to top edge (North)
	distances[1] = 1.0 - block_y;      // Distance to bottom edge (South)
	distances[2] = block_x;            // Distance to left edge (West)
	distances[3] = 1.0 - block_x;      // Distance to right edge (East)
	return find_closest_wall_face(distances);
}

void cast_ray(t_player *player, t_execution *execution, float angle, float *ray_x, float *ray_y)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	*ray_x = player->x;
	*ray_y = player->y;
	while (!touch(*ray_x, *ray_y, execution))
	{
		*ray_x += cos_angle;
		*ray_y += sin_angle;
		if (*ray_x < 0 || *ray_y < 0)
			break;
	}
}

void calculate_wall_dimensions(float dist, int *wall_start, int *wall_end)
{
	float	height;
	
	if (dist < 1)
		dist = 1;
	height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	*wall_start = (HEIGHT - height) / 2;
	*wall_end = *wall_start + height;
}
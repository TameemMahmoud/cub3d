/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:55:32 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/10 11:55:33 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

float	calculate_angle_diff(float delta_x, float delta_y, t_execution *game)
{
	float	angle;

	angle = atan2(delta_y, delta_x) - game->player.angle;
	return (angle);
}

float	fixed_dist(float ray_x, float ray_y, t_execution *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = ray_x - game->player.x;
	delta_y = ray_y - game->player.y;
	angle = calculate_angle_diff(delta_x, delta_y, game);
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

int	find_closest_wall_face(float *distances)
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
	return (direction);
}

int	get_wall_direction(float ray_x, float ray_y)
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
	distances[0] = block_y;
	distances[1] = 1.0 - block_y;
	distances[2] = block_x;
	distances[3] = 1.0 - block_x;
	return (find_closest_wall_face(distances));
}

void	calculate_wall_dimensions(float dist, int *wall_start, int *wall_end)
{
	float	height;

	if (dist < 1)
		dist = 1;
	height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	*wall_start = (HEIGHT - height) / 2;
	*wall_end = *wall_start + height;
}

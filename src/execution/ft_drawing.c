/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:55:49 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/15 13:17:35 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "cub3d.h"

void	cast_ray(t_player *player, t_execution *execution, float angle)
{
	float	cos_angle;
	float	sin_angle;
	float	step_size;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	execution->ray_x = player->x;
	execution->ray_y = player->y;
	step_size = 1.0;
	while (!touch(execution->ray_x, execution->ray_y, execution))
	{
		if (touch(execution->ray_x + cos_angle * step_size,
				execution->ray_y + sin_angle * step_size, execution))
			step_size = 0.005;
		execution->ray_x += cos_angle * step_size;
		execution->ray_y += sin_angle * step_size;
		if (execution->ray_x < 0 || execution->ray_y < 0)
			break ;
	}
}

void	draw_ceiling_floor(t_execution *execution, int column,
						int wall_start, int wall_end)
{
	int	y;

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

void	draw_line(t_player *player, t_execution *exec, float x, int i)
{
	float	dist;
	int		direction;

	cast_ray(player, exec, x);
	dist = fixed_dist(exec->ray_x, exec->ray_y, exec);
	calculate_wall_dimensions(dist, &exec->wall_start, &exec->wall_end);
	direction = get_wall_direction(exec->ray_x, exec->ray_y);
	draw_ceiling_floor(exec, i, exec->wall_start, exec->wall_end);
	draw_textured_wall(exec, i, direction);
}

int	draw_a_loop(t_execution *exec)
{
	float		fraction;
	float		start_x;
	int			i;
	t_player	*player;

	player = &exec->player;
	clear_image(exec);
	ft_player_movement(player, exec);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, exec, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(exec->mlx_data.mlx, exec->mlx_data.win,
		exec->mlx_data.img, 0, 0);
	return (0);
}

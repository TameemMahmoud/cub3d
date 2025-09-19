/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:56:02 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/15 17:22:00 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

t_texture	*get_wall_texture(t_execution *execution, int direction)
{
	if (direction == 0)
		return (&execution->north_texture);
	else if (direction == 1)
		return (&execution->south_texture);
	else if (direction == 2)
		return (&execution->west_texture);
	else
		return (&execution->east_texture);
}

int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	int	color;
	int	*pixels;

	if (!texture || !texture->data)
		return (0xFF00FF);
	pixels = (int *)texture->data;
	if (tex_x < 0 || tex_y < 0 || tex_x >= texture->width
		|| tex_y >= texture->height)
		return (0xFF00FF);
	color = pixels[tex_y * texture->width + tex_x];
	return (color);
}

void	calculate_texture_x(t_execution *exec, int direction, int *tex_x)
{
	t_texture	*wall_texture;

	wall_texture = get_wall_texture(exec, direction);
	if (direction == 0 || direction == 1)
		*tex_x = (int)(fmod(exec->ray_x, BLOCK_SIZE) / BLOCK_SIZE
				* wall_texture->width);
	else
		*tex_x = (int)(fmod(exec->ray_y, BLOCK_SIZE) / BLOCK_SIZE
				* wall_texture->width);
	if (direction == 1 || direction == 3)
		*tex_x = wall_texture->width - *tex_x - 1;
}

void	draw_wall_pixel_column(t_execution *exec, int col, int direction,
		int tex_x)
{
	t_texture	*wall_texture;
	float		step;
	float		tex_pos;
	int			tex_y;
	int			y;

	wall_texture = get_wall_texture(exec, direction);
	step = (float)wall_texture->height / (exec->wall_end - exec->wall_start);
	tex_pos = 0;
	y = exec->wall_start;
	while (y < exec->wall_end && y < HEIGHT)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= wall_texture->height)
			tex_y = wall_texture->height - 1;
		my_mlx_pixel_put(col, y, exec, get_texture_color(wall_texture, tex_x,
				tex_y));
		tex_pos += step;
		y++;
	}
}

void	draw_textured_wall(t_execution *exec, int col, int direction)
{
	int	tex_x;

	calculate_texture_x(exec, direction, &tex_x);
	draw_wall_pixel_column(exec, col, direction, tex_x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:56:02 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/10 11:56:03 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	int	pixel_index;

	if (!texture || !texture->data)
		return (0xFFFFFF);
	if (tex_x < 0 || tex_x >= texture->width
		|| tex_y < 0 || tex_y >= texture->height)
		return (0xFFFFFF);
	pixel_index = (tex_y * texture->line_length)
		+ (tex_x * (texture->bits_per_pixel / 8));
	return (*(int *)(texture->data + pixel_index));
}

t_texture	*select_texture_by_direction(t_execution *execution, int direction)
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

int	calculate_texture_x(float ray_x, float ray_y, int dir, t_texture *texture)
{
	int	tex_x;

	if (dir == 0 || dir == 1)
		tex_x = (int)(ray_x) % BLOCK_SIZE;
	else
		tex_x = (int)(ray_y) % BLOCK_SIZE;
	tex_x = (tex_x * texture->width) / BLOCK_SIZE;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

void	draw_texture_column(t_execution *execution, int column,
			t_texture *texture, int tex_x)
{
	int	y;
	int	tex_y;
	int	color;

	y = execution->wall_start;
	while (y < execution->wall_end && y < HEIGHT)
	{
		tex_y = ((y - execution->wall_start) * texture->height)
			/ (execution->wall_end - execution->wall_start);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		color = get_texture_color(texture, tex_x, tex_y);
		my_mlx_pixel_put(column, y, execution, color);
		y++;
	}
}

void	draw_textured_wall(t_execution *execution, int column, int direction)
{
	t_texture	*current_texture;
	int			tex_x;

	current_texture = select_texture_by_direction(execution, direction);
	if (!current_texture || !current_texture->data)
	{
		draw_error_pattern(execution, column, execution->wall_start,
			execution->wall_end);
		return ;
	}
	tex_x = calculate_texture_x(execution->ray_x, execution->ray_y,
			direction, current_texture);
	draw_texture_column(execution, column, current_texture, tex_x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:47:56 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/15 17:49:40 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

void	my_mlx_pixel_put(int x, int y, t_execution *execution, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = execution->mlx_data.pixels_ptr + (y * execution->mlx_data.line_length
			+ x * (execution->mlx_data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

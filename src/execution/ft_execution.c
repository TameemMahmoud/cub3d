/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:55:52 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/10 11:55:53 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "cub3d.h"

void	clear_image(t_execution *execution)
{
	int	i;

	i = 0;
	while (i < (WIDTH * HEIGHT))
	{
		((int *)execution->mlx_data.pixels_ptr)[i] = 0x000000;
		i++;
	}
}

bool	touch(float px, float py, t_execution *execution)
{
	int	x;
	int	y;

	x = (int)(px / BLOCK_SIZE);
	y = (int)(py / BLOCK_SIZE);
	if (y < 0 || x < 0)
		return (true);
	if (!execution->map || !execution->map[y])
		return (true);
	if (execution->map[y][x] == '\0')
		return (true);
	if (execution->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

int	close_window(t_execution *execution)
{
	mlx_destroy_window(execution->mlx_data.mlx, execution->mlx_data.win);
	exit(0);
	return (0);
}

void	execution(t_src *src)
{
	t_execution	cub3d;

	ft_init_cub3d(&cub3d, src);
	ft_init_player(&cub3d.player, src);
	mlx_hook(cub3d.mlx_data.win, 2, 1L << 0, key_press, &cub3d.player);
	mlx_hook(cub3d.mlx_data.win, 3, 1L << 1, key_release, &cub3d.player);
	mlx_hook(cub3d.mlx_data.win, 17, 1L << 17, close_window, &cub3d);
	mlx_loop_hook(cub3d.mlx_data.mlx, draw_a_loop, &cub3d);
	mlx_loop(cub3d.mlx_data.mlx);
}

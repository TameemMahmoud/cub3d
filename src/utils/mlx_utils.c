#include "cub3d.h"
#include "execution.h"

void	my_mlx_pixel_put(int x, int y, t_execution *execution, int color)
{
	char	*dst;
	
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return;
	dst = execution->mlx_data.pixels_ptr + (y * execution->mlx_data.line_length + x * (execution->mlx_data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
#include "cub3d.h"
#include "execution.h"

void	my_mlx_pixel_put(int x, int y, t_execution *execution, int color)
{
	char	*dst;
	
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return;
	dst = execution->pixels_ptr + (y * execution->line_length + x * (execution->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
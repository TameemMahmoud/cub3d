#include "execution.h"
#include "cub3d.h"

void draw_ceiling_floor(t_execution *execution, int column, int wall_start, int wall_end)
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

void draw_solid_color_wall(t_execution *execution, int column, 
                          int wall_start, int wall_end, int direction)
{
    int	color;
    int	y;
    
    if (direction == 0)
        color = 0xFF0000;
    else if (direction == 1)
        color = 0x00FF00;
    else if (direction == 2)
        color = 0x0000FF;
    else
        color = 0xFFFF00;
    y = wall_start;
    while (y < wall_end && y < HEIGHT)
    {
        my_mlx_pixel_put(column, y, execution, color);
        y++;
    }
}

void	draw_line(t_player *player, t_execution *execution, float x, int i)
{
    float	ray_x;
    float	ray_y;
    float	dist;
    int		direction;

    cast_ray(player, execution, x, &ray_x, &ray_y);
    execution->ray_x = ray_x;
    execution->ray_y = ray_y;
    dist = fixed_dist(player->x, player->y, ray_x, ray_y, execution);
    calculate_wall_dimensions(dist, &execution->wall_start, &execution->wall_end);
    direction = get_wall_direction(ray_x, ray_y);
    draw_ceiling_floor(execution, i, execution->wall_start, execution->wall_end);
    draw_textured_wall(execution, i, direction);
}

int draw_a_loop(t_execution *execution)
{
    float		fraction;
    float		start_x;
    int			i;
    t_player	*player;

    player = &execution->player;
    clear_image(execution);		
    ft_player_movement(player, execution);
    fraction = PI / 3 / WIDTH;
    start_x = player->angle - PI / 6;
    i = 0;
    while(i < WIDTH)
    {
        draw_line(player, execution, start_x, i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(execution->mlx, execution->win, execution->img, 0, 0);
    return (0);
}


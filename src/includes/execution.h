#ifndef EXECUTION_H
#define EXECUTION_H

#include "cub3d.h"
#include "keycodes.h"

#define WIDTH 1280
#define HEIGHT 720
#define PLAYER_SPEED 3
#define BLOCK_SIZE 64
#define PLAYER_SIZE 10
#define ANGLE_SPEED 0.03

#define PI 3.14159265358979323846

typedef struct s_texture {
    void    *img;
    char    *data;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_texture;

typedef struct player
{
    float   x;
    float   y;
    float   angle;
    bool    key_up;
    bool    key_down;
    bool    key_left;
    bool    key_right;
    bool    key_rotate_left;
    bool    key_rotate_right;
} t_player;

typedef struct execution
{
    void *mlx;
    void *win;
    void *img;
    char *pixels_ptr;
    int bits_per_pixel;
    int line_length;
    int endian;
    t_player player;
    
    char **map;
    int floor_color;
    int ceiling_color;
    
    // Raycasting data
    float ray_x;
    float ray_y;
    int wall_start;
    int wall_end;

    // Texture support
    t_texture north_texture;
    t_texture south_texture;
    t_texture east_texture;
    t_texture west_texture;
} t_execution;

//ft_execution.c
void	execution(t_src *src);
void	exit_failure(char *err_msg);
float	distance(float x, float y);
bool	touch(float px, float py, t_execution *execution);
void	clear_image(t_execution *execution);

//ft_player.c
void	ft_init_player(t_player *player, t_src *src);
int		key_release(int keycode, t_player *player);
int		key_press(int keycode, t_player *player);
void	ft_player_movement(t_player *player, t_execution *execution);
bool	check_collision(float new_x, float new_y, t_execution *execution);
void	move_forward_backward(t_player *player, t_execution *execution);
void	move_left_right(t_player *player, t_execution *execution);


//ft_init_cub3d.c
void    ft_init_cub3d(t_execution *cub3d, t_src *src);
void    load_all_textures(t_execution *cub3d, t_src *src);

//ft_drawing.c
int     draw_a_loop(t_execution *execution);
void    draw_solid_color_wall(t_execution *execution, int column, int wall_start, int wall_end, int direction);


//ft_calculation.c
float	fixed_dist(float x1, float y1, float x2, float y2, t_execution *game);
int		get_wall_direction(float ray_x, float ray_y);
void    calculate_wall_dimensions(float dist, int *wall_start, int *wall_end);
void    cast_ray(t_player *player, t_execution *execution, float angle, float *ray_x, float *ray_y);

//ft_textures.c
void    draw_textured_wall(t_execution *execution, int column, int direction);
//mlx_utils.c
void my_mlx_pixel_put(int x, int y, t_execution *execution, int color);

#endif
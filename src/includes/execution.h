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


typedef struct player
{
	// t_execution *execution;
	float x;
	float y;
	float angle; // Player's direction in radians
	float cos_angle; // Cosine of the angle for movement calculations
	float sin_angle; // Sine of the angle for movement calculations
	float new_x;
	float new_y;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

	bool key_rotate_left;
	bool key_rotate_right;
} t_player;

typedef struct execution
{
	void *mlx;
	void *win;
	void *img;
	char *pixels_ptr;
	char *img_data;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_player player;

	char **map;
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

//ft_init_cub3d.c
void ft_init_cub3d(t_execution *cub3d, t_src *src);

//ft_drawing.c
void	draw_square(int x, int y, t_execution *execution, int size, int color);
void	draw_map(t_execution *execution);
int		draw_a_loop(t_execution *execution);
void	draw_line(t_player *player, t_execution *execution, float x, int i);


//mlx_utils.c
void	my_mlx_pixel_put(int x, int y, t_execution *execution, int color);

#endif
#ifndef EXECUTION_H
#define EXECUTION_H

#include "cub3d.h"

#define WIDTH 1280
#define HEIGHT 720
#define PLAYER_SPEED 3
#define BLOCK_SIZE 20
#define PLAYER_SIZE 10
#define ANGLE_SPEED 0.03

/*
Player Movement Keys
*/
#define W 13
#define A 0
#define S 1
#define D 2

/*
Player Rotation Keys
*/
#define LEFT 123
#define RIGHT 124
#define UP 126
#define DOWN 125


#define PI 3.14159265358979323846
#define ESC 53


typedef struct player
{
	// t_execution *execution;
	float x;
	float y;
	float angle; // Player's direction in radians
	float cos_angle; // Cosine of the angle for movement calculations
	float sin_angle; // Sine of the angle for movement calculations

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



void	execution(t_src *src);
void	init_cub3d(t_execution *cub3d, t_src *src);
void	exit_failure(char *err_msg);

void	init_player(t_player *player);
int		key_release(int keycode, t_player *player);
int		key_press(int keycode, t_player *player);
void	player_movement(t_player *player);


#endif
#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "mlx/mlx.h"
# include <math.h>

// ---------- const strings--------------
# define INVALID_FILE_NAME "Error\nInvalid file, kindly check the file name.\n"
# define INVALID_EXTENSION "Error\nInvalid file extention.\n"
# define INVALID_FD "Error\nINVALID_FD"

typedef struct s_textures {
	char *north;
	char *south;
	char *west;
	char *east;
} t_textures;

typedef struct s_colors {
	int floor_r, floor_g, floor_b;
	int ceiling_r, ceiling_g, ceiling_b;
	int floor_set, ceiling_set;
} t_colors;

typedef struct s_file {
	char    **file_map;
	int     file_len;
	int     map_start_index;
} t_file;

typedef struct s_map {
	char    **grid;
	int     width;
	int     height;
	int     player_x;
	int     player_y;
	char    player_dir;
} t_map;

typedef struct s_src
{
	void        *mlx_ptr;
	void        *win_ptr;
	t_file      file;
	t_map       *map;
	t_textures  textures;
	t_colors    colors;
} t_src;

// Function prototypes
void    cub3d(char *file);
void    init(t_src *src);
void    parsing(t_src *src, char *input_file);
void    parse_config_elements(t_src *src);
void    exit_failure_clear(t_src *src, char *err_msg);
void    exit_failure(char *err_msg);
void	exit_success_clear(t_src *src);
void	cleanup_all(t_src *src);
void	parse_map(t_src *src);
int		is_empty_line(char *line);
#endif
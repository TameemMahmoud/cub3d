#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include <stdio.h>
# include "mlx/mlx.h"
# include <math.h>


// ---------- const strings--------------

# define INVALID_FILE_NAME "Error\nInvalid file, kindly check the file name.\n"


typedef struct s_file
{
	char		**file_arr;
	int			filepath_len;
	int			stage;
	int			file_len;
}				t_file;

typedef struct s_map
{
	char		**map_arr;
	int			map_width;
	int			map_height;
	int			map_st;
	int			map_end;
	int			wall_counter;
	int			p_counter;
	int			p_x;
	int			p_y;
	char		p_direction;
}				t_map;

typedef struct s_src
{
    void		*mlx_ptr;
	void		*win_ptr;
    t_file      file;
    t_map       *map;
}               t_src;

void cub3d(char *file);
void init(t_src *src, char *file);
#endif
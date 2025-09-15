/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:49:36 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/14 19:40:18 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "mlx/mlx.h"
# include <string.h>
# include <math.h>

// ---------- const strings--------------
# define INVALID_FILE_NAME "Error\nInvalid file, kindly check the file name.\n"
# define INVALID_EXTENSION "Error\nInvalid file extention.\n"
# define INVALID_FD "Error\nINVALID_FD"

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_colors
{
	int	floor_r;
	int	floor_g;
	int	floor_b;
	int	ceiling_r;
	int	ceiling_g;
	int	ceiling_b;
	int	floor_set;
	int	ceiling_set;
}	t_colors;

typedef struct s_file
{
	char	**file_map;
	int		file_len;
	int		map_start_index;
}	t_file;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_src
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_file		file;
	t_map		*map;
	t_textures	textures;
	t_colors	colors;
}	t_src;

// Function prototypes
void	cub3d(char *file);
void	init(t_src *src);
void	parsing(t_src *src, char *input_file);
void	parse_config_elements(t_src *src);
void	exit_failure_clear(t_src *src, char *err_msg);
void	exit_failure(char *err_msg);
void	exit_success_clear(t_src *src);
void	cleanup_all(t_src *src);
void	parse_map(t_src *src);
int		is_empty_line(char *line);
void	parse_texture(t_src *src, char *line);
int		check_duplicate_texture(t_src *src, char *id);
char	*get_duplicate_error_msg(char *id);
void	parse_color(t_src *src, char *line);
int		validate_color_values(char **rgb);
int		check_duplicate_color(t_src *src, char *id);
void	store_color_values(t_src *src, char *id, char **rgb);
void	free_split(char **split);
void	handle_duplicate_error(t_src *src, char *id, char *color);
void	handle_format_error(t_src *src, char *id, char *color, char **rgb);
void	extract_map_lines(t_src *src, char ***map_lines, int *height);
void	allocate_map_structure(t_src *src);
void	validate_map_chars(t_src *src, char **map_lines, int height);
void	find_player(t_src *src, char **map_lines, int height);
void	exit_failure_clear_lines(t_src *src, char *err_msg,
			char **map_lines, int height);
#endif
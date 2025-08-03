
#include "../includes/cub3d.h"

static void	free_textures(t_textures *textures)
{
	if (textures->north)
	{
		free(textures->north);
		textures->north = NULL;
	}
	if (textures->south)
	{
		free(textures->south);
		textures->south = NULL;
	}
	if (textures->west)
	{
		free(textures->west);
		textures->west = NULL;
	}
	if (textures->east)
	{
		free(textures->east);
		textures->east = NULL;
	}
}

static void	free_file_map(t_file *file)
{
	int	i;

	if (!file->file_map)
		return ;
	i = 0;
	while (i < file->file_len)
	{
		if (file->file_map[i])
		{
			free(file->file_map[i]);
			file->file_map[i] = NULL;
		}
		i++;
	}
	free(file->file_map);
	file->file_map = NULL;
}

static void	free_map_grid(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
		}
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

static void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_map_grid(map);
	free(map);
}

// static void	cleanup_mlx(t_src *src)
// {
// 	if (src->win_ptr)
// 	{
// 		mlx_destroy_window(src->mlx_ptr, src->win_ptr);
// 		src->win_ptr = NULL;
// 	}
// 	if (src->mlx_ptr)
// 	{
// 		mlx_destroy_display(src->mlx_ptr);
// 		free(src->mlx_ptr);
// 		src->mlx_ptr = NULL;
// 	}
// }

void	cleanup_all(t_src *src)
{
	if (!src)
		return ;
	free_textures(&src->textures);
	free_file_map(&src->file);
	free_map(src->map);
	src->map = NULL;
	// cleanup_mlx(src);
}

void	exit_failure_clear(t_src *src, char *err_msg)
{
	cleanup_all(src);
	ft_putendl_fd(err_msg, 2);
	exit(1);
}

void	exit_success_clear(t_src *src)
{
	cleanup_all(src);
	exit(0);
}

void	exit_failure(char *err_msg)
{
	if (*err_msg)
		printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}
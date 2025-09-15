/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:30:35 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/14 20:51:12 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

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
}

/*
** Integrated cleanup for both parsing and execution phases
*/
void	cleanup_all_phases(t_src *src, t_execution *execution)
{
	if (execution)
	{
		if (execution->north_texture.img && execution->mlx_data.mlx)
			mlx_destroy_image(execution->mlx_data.mlx, execution->north_texture.img);
		if (execution->south_texture.img && execution->mlx_data.mlx)
			mlx_destroy_image(execution->mlx_data.mlx, execution->south_texture.img);
		if (execution->east_texture.img && execution->mlx_data.mlx)
			mlx_destroy_image(execution->mlx_data.mlx, execution->east_texture.img);
		if (execution->west_texture.img && execution->mlx_data.mlx)
			mlx_destroy_image(execution->mlx_data.mlx, execution->west_texture.img);
		if (execution->mlx_data.img && execution->mlx_data.mlx)
			mlx_destroy_image(execution->mlx_data.mlx, execution->mlx_data.img);
		if (execution->mlx_data.win && execution->mlx_data.mlx)
			mlx_destroy_window(execution->mlx_data.mlx, execution->mlx_data.win);
	}
	cleanup_all(src);
}

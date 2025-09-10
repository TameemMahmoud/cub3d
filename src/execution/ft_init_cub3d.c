/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:55:55 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/10 11:55:56 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/*Initializing Textures*/
void	load_texture(t_execution *cub3d, t_texture *texture, char *path)
{
	printf("Attempting to load texture: %s\n", path);
	texture->img = NULL;
	texture->data = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->img = mlx_xpm_file_to_image(cub3d->mlx_data.mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Warning: Failed to load texture: %s\n", path);
		return ;
	}
	printf("Successfully loaded texture: %s (Size: %dx%d)\n", path, texture->width, texture->height);
	texture->data = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->data)
	{
		printf("Warning: Failed to get texture data for: %s\n", path);
		texture->img = NULL;
		return ;
	}
}

void	load_all_textures(t_execution *cub3d, t_src *src)
{
	printf("Loading textures...\n");
	load_texture(cub3d, &cub3d->north_texture, src->textures.north);
	load_texture(cub3d, &cub3d->south_texture, src->textures.south);
	load_texture(cub3d, &cub3d->west_texture, src->textures.west);
	load_texture(cub3d, &cub3d->east_texture, src->textures.east);
	printf("Texture loading completed!\n");
}

void	ft_init_cub3d(t_execution *cub3d, t_src *src)
{
	cub3d->map = src->map->grid;
	cub3d->floor_color = rgb_to_hex(src->colors.floor_r, src->colors.floor_g,
			src->colors.floor_b);
	cub3d->ceiling_color = rgb_to_hex(src->colors.ceiling_r,
			src->colors.ceiling_g, src->colors.ceiling_b);
	printf("Initializing MLX...\n");
	cub3d->mlx_data.mlx = mlx_init();
	if (!cub3d->mlx_data.mlx)
		exit_failure("Error initializing MLX");
	cub3d->mlx_data.win = mlx_new_window(cub3d->mlx_data.mlx, WIDTH,
			HEIGHT, "Cub3D");
	if (!cub3d->mlx_data.win)
		exit_failure("Error creating window");
	cub3d->mlx_data.img = mlx_new_image(cub3d->mlx_data.mlx, WIDTH, HEIGHT);
	if (!cub3d->mlx_data.img)
		exit_failure("Error creating image");
	cub3d->mlx_data.pixels_ptr = mlx_get_data_addr(cub3d->mlx_data.img,
			&cub3d->mlx_data.bits_per_pixel,
			&cub3d->mlx_data.line_length, &cub3d->mlx_data.endian);
	if (!cub3d->mlx_data.pixels_ptr)
		exit_failure("Error getting image data address");
	load_all_textures(cub3d, src);
}

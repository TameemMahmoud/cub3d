/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:50:18 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/15 17:50:48 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

/*
** Cleanup textures
*/
void	cleanup_textures(t_execution *execution)
{
	if (execution->mlx_data.mlx)
	{
		if (execution->north_texture.img)
			mlx_destroy_image(execution->mlx_data.mlx,
				execution->north_texture.img);
		if (execution->south_texture.img)
			mlx_destroy_image(execution->mlx_data.mlx,
				execution->south_texture.img);
		if (execution->east_texture.img)
			mlx_destroy_image(execution->mlx_data.mlx,
				execution->east_texture.img);
		if (execution->west_texture.img)
			mlx_destroy_image(execution->mlx_data.mlx,
				execution->west_texture.img);
	}
}

/*
** Integrated cleanup for both parsing and execution phases
*/
void	cleanup_all_phases(t_src *src, t_execution *execution)
{
	if (execution)
	{
		cleanup_textures(execution);
		if (execution->mlx_data.img)
			mlx_destroy_image(execution->mlx_data.mlx, execution->mlx_data.img);
		if (execution->mlx_data.mlx && execution->mlx_data.win)
			mlx_destroy_window(execution->mlx_data.mlx,
				execution->mlx_data.win);
	}
	cleanup_all(src);
}

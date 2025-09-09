/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:13:29 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/08/07 20:45:56 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	store_north_south_textures(t_src *src, char *id, char *path)
{
	if (ft_strncmp(id, "NO", 2) == 0)
	{
		if (src->textures.north)
			exit_failure_clear(src, "Error\nDuplicate NO texture");
		src->textures.north = ft_strdup(path);
		if (!src->textures.north)
			exit_failure_clear(src, "Error\nMalloc error");
	}
	else if (ft_strncmp(id, "SO", 2) == 0)
	{
		if (src->textures.south)
			exit_failure_clear(src, "Error\nDuplicate SO texture");
		src->textures.south = ft_strdup(path);
		if (!src->textures.south)
			exit_failure_clear(src, "Error\nMalloc error");
	}
}

static void	store_west_east_textures(t_src *src, char *id, char *path)
{
	if (ft_strncmp(id, "WE", 2) == 0)
	{
		if (src->textures.west)
			exit_failure_clear(src, "Error\nDuplicate WE texture");
		src->textures.west = ft_strdup(path);
		if (!src->textures.west)
			exit_failure_clear(src, "Error\nMalloc error");
	}
	else if (ft_strncmp(id, "EA", 2) == 0)
	{
		if (src->textures.east)
			exit_failure_clear(src, "Error\nDuplicate EA texture");
		src->textures.east = ft_strdup(path);
		if (!src->textures.east)
			exit_failure_clear(src, "Error\nMalloc error");
	}
}

static void	store_texture_path(t_src *src, char *id, char *path)
{
	store_north_south_textures(src, id, path);
	store_west_east_textures(src, id, path);
}

void	parse_texture(t_src *src, char *line)
{
	char	*identifier;
	char	*trimmed_line;

	while (*line == ' ' || *line == '\t')
		line++;
	identifier = ft_substr(line, 0, 2);
	if (!identifier)
		exit_failure_clear(src, "Error\nMalloc error");
	line += 3;
	while (*line == ' ' || *line == '\t')
		line++;
	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
	{
		free(identifier);
		exit_failure_clear(src, "Error\nMalloc error");
	}
	store_texture_path(src, identifier, trimmed_line);
	free(identifier);
	free(trimmed_line);
}

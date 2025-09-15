/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:13:29 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/08 17:58:54 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	cleanup_and_exit(t_src *src, char *id, char *trimmed, char *msg)
{
	free(id);
	free(trimmed);
	exit_failure_clear(src, msg);
}

static void	store_north_south_textures(t_src *src, char *id, char *path)
{
	if (ft_strncmp(id, "NO", 2) == 0)
	{
		src->textures.north = ft_strdup(path);
		if (!src->textures.north)
			return ;
	}
	else if (ft_strncmp(id, "SO", 2) == 0)
	{
		src->textures.south = ft_strdup(path);
		if (!src->textures.south)
			return ;
	}
}

static void	store_west_east_textures(t_src *src, char *id, char *path)
{
	if (ft_strncmp(id, "WE", 2) == 0)
	{
		src->textures.west = ft_strdup(path);
		if (!src->textures.west)
			return ;
	}
	else if (ft_strncmp(id, "EA", 2) == 0)
	{
		src->textures.east = ft_strdup(path);
		if (!src->textures.east)
			return ;
	}
}

static int	check_malloc_failure(t_src *src, char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0 && !src->textures.north)
		return (1);
	if (ft_strncmp(id, "SO", 2) == 0 && !src->textures.south)
		return (1);
	if (ft_strncmp(id, "WE", 2) == 0 && !src->textures.west)
		return (1);
	if (ft_strncmp(id, "EA", 2) == 0 && !src->textures.east)
		return (1);
	return (0);
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
		cleanup_and_exit(src, identifier, NULL, "Error\nMalloc error");
	if (check_duplicate_texture(src, identifier))
		cleanup_and_exit(src, identifier, trimmed_line,
			get_duplicate_error_msg(identifier));
	store_north_south_textures(src, identifier, trimmed_line);
	store_west_east_textures(src, identifier, trimmed_line);
	if (check_malloc_failure(src, identifier))
		cleanup_and_exit(src, identifier, trimmed_line, "Error\nMalloc error");
	free(identifier);
	free(trimmed_line);
}

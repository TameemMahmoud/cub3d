/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:59:11 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 17:45:16 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_lines(t_src *src)
{
	int	i;
	int	count;

	i = src->file.map_start_index;
	count = 0;
	while (is_empty_line(src->file.file_map[i]))
		i++;
	while (i < src->file.file_len)
	{
		if (is_empty_line(src->file.file_map[i]))
			break ;
		count++;
		i++;
	}
	return (count);
}

static void	cleanup_partial_map_lines(char **map_lines, int allocated_count)
{
	int	i;

	if (!map_lines)
		return ;
	i = 0;
	while (i < allocated_count)
	{
		if (map_lines[i])
			free(map_lines[i]);
		i++;
	}
	free(map_lines);
}

static void	allocate_and_trim_line(t_src *src, char ***map_lines,
	int map_index, int file_index)
{
	(*map_lines)[map_index] = ft_strtrim(src->file.file_map[file_index], "\n");
	if (!(*map_lines)[map_index])
	{
		cleanup_partial_map_lines(*map_lines, map_index);
		*map_lines = NULL;
		exit_failure_clear(src, "Error\nMalloc error");
	}
}

static void	fill_map_lines(t_src *src, char ***map_lines, int height)
{
	int	i;
	int	map_index;

	i = src->file.map_start_index;
	map_index = 0;
	while (is_empty_line(src->file.file_map[i]))
		i++;
	while (i < src->file.file_len && map_index < height)
	{
		if (!is_empty_line(src->file.file_map[i]))
		{
			allocate_and_trim_line(src, map_lines, map_index, i);
			map_index++;
		}
		i++;
	}
}

void	extract_map_lines(t_src *src, char ***map_lines, int *height)
{
	*height = count_map_lines(src);
	if (*height == 0)
		exit_failure_clear(src, "Error\nNo map found");
	*map_lines = (char **)ft_calloc(*height + 1, sizeof(char *));
	if (!*map_lines)
		exit_failure_clear(src, "Error\nMalloc error");
	fill_map_lines(src, map_lines, *height);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:59:11 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/08 21:11:37 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	count_map_lines(t_src *src)
{
	int	i;
	int	count;

	i = src->file.map_start_index;
	count = 0;
	while (i < src->file.file_len)
	{
		if (!is_empty_line(src->file.file_map[i]))
			count++;
		i++;
	}
	return (count);
}

void	extract_map_lines(t_src *src, char ***map_lines, int *height)
{
	int	i;
	int	map_index;

	*height = count_map_lines(src);
	if (*height == 0)
		exit_failure_clear(src, "Error\nNo map found");
	*map_lines = (char **)ft_calloc(*height + 1, sizeof(char *));
	if (!*map_lines)
		exit_failure_clear_lines(src, "Error\nMalloc error");
	i = src->file.map_start_index;
	map_index = 0;
	while (i < src->file.file_len)
	{
		if (!is_empty_line(src->file.file_map[i]))
		{
			(*map_lines)[map_index] = ft_strtrim(src->file.file_map[i], "\n");
			if (!(*map_lines)[map_index])
				exit_failure_clear(src, "Error\nMalloc error");
			map_index++;
		}
		i++;
	}
}

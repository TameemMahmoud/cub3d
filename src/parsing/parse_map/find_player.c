/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:16:49 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/14 22:43:31 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	save_player_position(t_src *src, char **map_lines, int i, int j)
{
	src->map->player_x = j;
	src->map->player_y = i;
	src->map->player_dir = map_lines[i][j];
	map_lines[i][j] = '0';
}

static void	check_map_line(t_src *src, char **map_lines, int i,
int *player_count)
{
	int	j;

	j = 0;
	while (map_lines[i][j])
	{
		if (is_player_char(map_lines[i][j]))
		{
			if (*player_count > 0)
				exit_failure_clear_lines(src, "Error\nMultiple players found",
					map_lines, src->map->height);
			save_player_position(src, map_lines, i, j);
			(*player_count)++;
		}
		j++;
	}
}

void	find_player(t_src *src, char **map_lines, int height)
{
	int	i;
	int	player_count;

	src->map->height = height;
	i = 0;
	player_count = 0;
	while (i < height)
	{
		check_map_line(src, map_lines, i, &player_count);
		i++;
	}
	if (player_count == 0)
		exit_failure_clear_lines(src,
			"Error\nNo player found", map_lines, height);
}

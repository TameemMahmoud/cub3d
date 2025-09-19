/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:39:09 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 17:45:29 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_map_width(char **map_lines, int height)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (i < height)
	{
		current_width = ft_strlen(map_lines[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

static char	get_map_char_at(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}

static int	is_walkable_space_enclosed(char **map, int x, int y, int height)
{
	int		directions[4][2];
	int		i;
	int		new_x;
	int		new_y;
	char	neighbor;

	directions[0][0] = 0;
	directions[0][1] = -1;
	directions[1][0] = 0;
	directions[1][1] = 1;
	directions[2][0] = -1;
	directions[2][1] = 0;
	directions[3][0] = 1;
	directions[3][1] = 0;
	i = 0;
	while (i < 4)
	{
		new_x = x + directions[i][0];
		new_y = y + directions[i][1];
		neighbor = get_map_char_at(map, new_x, new_y, height);
		if (neighbor == ' ')
			return (0);
		i++;
	}
	return (1);
}

static void	validate_map_walls(t_src *src, char **map_lines, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < (int)ft_strlen(map_lines[i]))
		{
			if (map_lines[i][j] == '0')
			{
				if (!is_walkable_space_enclosed(map_lines, j, i, height))
					exit_failure_clear_lines(src,
						"Error\nMap not closed by walls", map_lines, height);
			}
			j++;
		}
		i++;
	}
}

void	parse_map(t_src *src)
{
	char	**map_lines;
	int		height;

	allocate_map_structure(src);
	extract_map_lines(src, &map_lines, &height);
	validate_map_chars(src, map_lines, height);
	find_player(src, map_lines, height);
	validate_map_walls(src, map_lines, height);
	src->map->width = get_map_width(map_lines, height);
	src->map->height = height;
	src->map->grid = map_lines;
}

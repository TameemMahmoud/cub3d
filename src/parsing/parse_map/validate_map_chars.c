/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:12:24 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 17:45:33 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

void	validate_map_chars(t_src *src, char **map_lines, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (!is_valid_map_char(map_lines[i][j]))
				exit_failure_clear_lines(src, "Error\nInvalid character in map",
					map_lines, height);
			j++;
		}
		i++;
	}
}

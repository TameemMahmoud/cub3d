/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:07:53 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/14 22:56:07 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_map_lines(char **map_lines, int height)
{
	int	i;

	if (!map_lines)
		return ;
	i = 0;
	while (i < height && map_lines[i])
	{
		free(map_lines[i]);
		map_lines[i] = NULL;
		i++;
	}
	free(map_lines);
}

void	exit_failure_clear_lines(t_src *src, char *err_msg,
	char **map_lines, int height)
{
	free_map_lines(map_lines, height);
	exit_failure_clear(src, err_msg);
}

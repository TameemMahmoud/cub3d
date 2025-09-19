/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:08:50 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 17:46:23 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_rgb_range(int value)
{
	return (value >= 0 && value <= 255);
}

int	validate_color_values(char **rgb)
{
	int	r;
	int	g;
	int	b;

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (!is_valid_rgb_range(r) || !is_valid_rgb_range(g)
		|| !is_valid_rgb_range(b))
		return (0);
	return (1);
}

int	check_duplicate_color(t_src *src, char *id)
{
	if (ft_strncmp(id, "F", 1) == 0 && src->colors.floor_set)
		return (1);
	if (ft_strncmp(id, "C", 1) == 0 && src->colors.ceiling_set)
		return (1);
	return (0);
}

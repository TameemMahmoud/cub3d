/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_storage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:09:32 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/08 18:09:37 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	store_floor_color(t_src *src, int r, int g, int b)
{
	src->colors.floor_r = r;
	src->colors.floor_g = g;
	src->colors.floor_b = b;
	src->colors.floor_set = 1;
}

static void	store_ceiling_color(t_src *src, int r, int g, int b)
{
	src->colors.ceiling_r = r;
	src->colors.ceiling_g = g;
	src->colors.ceiling_b = b;
	src->colors.ceiling_set = 1;
}

void	store_color_values(t_src *src, char *id, char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (ft_strncmp(id, "F", 1) == 0)
		store_floor_color(src, r, g, b);
	else if (ft_strncmp(id, "C", 1) == 0)
		store_ceiling_color(src, r, g, b);
}

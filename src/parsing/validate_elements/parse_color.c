/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:19:51 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/08/07 20:35:32 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	validate_color_values(char **rgb)
{
	int	r;
	int	g;
	int	b;

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

static void	store_color_values(t_src *src, char *id, char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (ft_strncmp(id, "F", 1) == 0)
	{
		if (src->colors.floor_set)
			exit_failure_clear(src, "Error\nDuplicate floor color");
		src->colors.floor_r = r;
		src->colors.floor_g = g;
		src->colors.floor_b = b;
		src->colors.floor_set = 1;
	}
	else if (ft_strncmp(id, "C", 1) == 0)
	{
		if (src->colors.ceiling_set)
			exit_failure_clear(src, "Error\nDuplicate ceiling color");
		src->colors.ceiling_r = r;
		src->colors.ceiling_g = g;
		src->colors.ceiling_b = b;
		src->colors.ceiling_set = 1;
	}
}

void	parse_color(t_src *src, char *line)
{
	char	*identifier;
	char	*color_str;
	char	**rgb_values;

	while (*line == ' ' || *line == '\t')
		line++;
	identifier = ft_substr(line, 0, 1);
	if (!identifier)
		exit_failure_clear(src, "Error\nMalloc error");
	line += 2;
	while (*line == ' ' || *line == '\t')
		line++;
	color_str = ft_strtrim(line, "\n");
	if (!color_str)
	{
		free(identifier);
		exit_failure_clear(src, "Error\nMalloc error");
	}
	rgb_values = ft_split(color_str, ',');
	if (!validate_color_values(rgb_values))
		exit_failure_clear(src, "Error\nInvalid color format");
	store_color_values(src, identifier, rgb_values);
	free(identifier);
	free(color_str);
	free_split(rgb_values);
}

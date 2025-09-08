/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:19:51 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/08 18:13:52 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*extract_identifier(t_src *src, char *line)
{
	char	*identifier;

	while (*line == ' ' || *line == '\t')
		line++;
	identifier = ft_substr(line, 0, 1);
	if (!identifier)
		exit_failure_clear(src, "Error\nMalloc error");
	return (identifier);
}

static char	*extract_color_string(t_src *src, char *line, char *id)
{
	char	*color_str;

	line += 2;
	while (*line == ' ' || *line == '\t')
		line++;
	color_str = ft_strtrim(line, "\n");
	if (!color_str)
	{
		free(id);
		exit_failure_clear(src, "Error\nMalloc error");
	}
	return (color_str);
}

void	parse_color(t_src *src, char *line)
{
	char	*identifier;
	char	*color_str;
	char	**rgb_values;

	identifier = extract_identifier(src, line);
	color_str = extract_color_string(src, line, identifier);
	if (check_duplicate_color(src, identifier))
		handle_duplicate_error(src, identifier, color_str);
	rgb_values = ft_split(color_str, ',');
	if (!validate_color_values(rgb_values))
		handle_format_error(src, identifier, color_str, rgb_values);
	store_color_values(src, identifier, rgb_values);
	free(identifier);
	free(color_str);
	free_split(rgb_values);
}

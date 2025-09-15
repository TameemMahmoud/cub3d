/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:37:06 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 17:46:23 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_duplicate_texture(t_src *src, char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0 && src->textures.north)
		return (1);
	if (ft_strncmp(id, "SO", 2) == 0 && src->textures.south)
		return (1);
	if (ft_strncmp(id, "WE", 2) == 0 && src->textures.west)
		return (1);
	if (ft_strncmp(id, "EA", 2) == 0 && src->textures.east)
		return (1);
	return (0);
}

char	*get_duplicate_error_msg(char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0)
		return ("Error\nDuplicate NO texture");
	if (ft_strncmp(id, "SO", 2) == 0)
		return ("Error\nDuplicate SO texture");
	if (ft_strncmp(id, "WE", 2) == 0)
		return ("Error\nDuplicate WE texture");
	if (ft_strncmp(id, "EA", 2) == 0)
		return ("Error\nDuplicate EA texture");
	return ("Error\nDuplicate texture");
}

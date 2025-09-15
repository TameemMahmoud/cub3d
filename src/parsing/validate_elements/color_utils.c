/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:09:54 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 17:45:53 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **split)
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

static void	cleanup_memory(char *id, char *color, char **rgb)
{
	free(id);
	free(color);
	free_split(rgb);
}

static char	*get_duplicate_msg(char *id)
{
	if (ft_strncmp(id, "F", 1) == 0)
		return ("Error\nDuplicate floor color");
	return ("Error\nDuplicate ceiling color");
}

void	handle_duplicate_error(t_src *src, char *id, char *color)
{
	char	*msg;

	msg = get_duplicate_msg(id);
	cleanup_memory(id, color, NULL);
	exit_failure_clear(src, msg);
}

void	handle_format_error(t_src *src, char *id, char *color, char **rgb)
{
	cleanup_memory(id, color, rgb);
	exit_failure_clear(src, "Error\nInvalid color format");
}

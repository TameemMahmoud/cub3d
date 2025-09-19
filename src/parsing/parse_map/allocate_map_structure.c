/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map_structure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:56:58 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 17:45:07 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocate_map_structure(t_src *src)
{
	src->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!src->map)
		exit_failure_clear(src, "Error\nMalloc error");
}

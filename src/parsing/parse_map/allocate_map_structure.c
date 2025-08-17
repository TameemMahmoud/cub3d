/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map_structure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:56:58 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/08/07 21:01:57 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	allocate_map_structure(t_src *src)
{
	src->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!src->map)
		exit_failure_clear(src, "Error\nMalloc error");
}

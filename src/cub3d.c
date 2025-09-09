/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:23:33 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/08/03 19:23:50 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

void	cub3d(char *file)
{
	t_src	src;
	int		len;

	len = ft_strlen(file);
	if ((len - 4) <= 0 || ft_strncmp(".cub", file + (len - 4), len))
	{
		printf(INVALID_EXTENSION);
		exit(EXIT_FAILURE);
	}
	init(&src);
	parsing(&src, file);
	execution(&src);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:33:33 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/08/03 19:34:18 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_failure_clear(t_src *src, char *err_msg)
{
	cleanup_all(src);
	ft_putendl_fd(err_msg, 2);
	exit(1);
}

void	exit_success_clear(t_src *src)
{
	cleanup_all(src);
	exit(0);
}

void	exit_failure(char *err_msg)
{
	if (*err_msg)
		printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}

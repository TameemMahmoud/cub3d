/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:33:33 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 12:03:16 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

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

void	exit_failure(char *err_msg, t_src *src)
{
	if (*err_msg)
		printf("%s\n", err_msg);
	cleanup_all(src);
	exit(EXIT_FAILURE);
}

/*
** Clean exit for execution phase with error message
*/
void	exit_execution(t_src *src, t_execution *execution, char *err_msg)
{
	if (err_msg)
		ft_putendl_fd(err_msg, 2);
	
	cleanup_all_phases(src, execution);
	exit(1);
}

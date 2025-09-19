/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:21:55 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 12:08:42 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "includes/execution.h"

int	main(int ac, char **av)
{
	if (ac == 2)
		cub3d(av[1]);
	else
		exit_failure("Invalid arguments", NULL);
	return (0);
}

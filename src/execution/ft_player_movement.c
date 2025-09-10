/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:09:22 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/10 12:11:28 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

void	move_with_sliding(t_player *player, t_execution *execution,
		float move_x, float move_y)
{
	float	new_x;
	float	new_y;

	new_x = player->x + move_x;
	new_y = player->y + move_y;
	if (!check_collision(new_x, new_y, execution))
	{
		player->x = new_x;
		player->y = new_y;
		return ;
	}
	else if (!check_collision(new_x, player->y, execution))
	{
		player->x = new_x;
		return ;
	}
	else if (!check_collision(player->x, new_y, execution))
	{
		player->y = new_y;
		return ;
	}
}

void	move_forward_backward(t_player *player, t_execution *execution)
{
	float	move_x;
	float	move_y;

	if (player->key_up)
	{
		move_x = cos(player->angle) * PLAYER_SPEED;
		move_y = sin(player->angle) * PLAYER_SPEED;
		move_with_sliding(player, execution, move_x, move_y);
	}
	else if (player->key_down)
	{
		move_x = -cos(player->angle) * PLAYER_SPEED;
		move_y = -sin(player->angle) * PLAYER_SPEED;
		move_with_sliding(player, execution, move_x, move_y);
	}
}

void	move_left_right(t_player *player, t_execution *execution)
{
	float	move_x;
	float	move_y;

	if (player->key_left)
	{
		move_x = cos(player->angle - PI / 2) * PLAYER_SPEED;
		move_y = sin(player->angle - PI / 2) * PLAYER_SPEED;
		move_with_sliding(player, execution, move_x, move_y);
	}
	else if (player->key_right)
	{
		move_x = cos(player->angle + PI / 2) * PLAYER_SPEED;
		move_y = sin(player->angle + PI / 2) * PLAYER_SPEED;
		move_with_sliding(player, execution, move_x, move_y);
	}
}

void	ft_player_movement(t_player *player, t_execution *execution)
{
	if (player->key_rotate_left)
		player->angle -= ANGLE_SPEED;
	else if (player->key_rotate_right)
		player->angle += ANGLE_SPEED;
	move_forward_backward(player, execution);
	move_left_right(player, execution);
}

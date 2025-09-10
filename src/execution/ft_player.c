/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:55:58 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/10 12:11:02 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"



int key_press(int keycode, t_player *player)
{
    if (keycode == KEY_W)
        player->key_up = true;
    else if (keycode == KEY_S)
        player->key_down = true;
    else if (keycode == KEY_A)
        player->key_left = true;
    else if (keycode == KEY_D)
        player->key_right = true;
    else if (keycode == KEY_LEFT)
        player->key_rotate_left = true;
    else if (keycode == KEY_RIGHT)
        player->key_rotate_right = true;
    else if (keycode == KEY_ESC)
        exit(0);
    return (0);
}

int key_release(int keycode, t_player *player)
{
    if (keycode == KEY_W)
        player->key_up = false;
    else if (keycode == KEY_S)
        player->key_down = false;
    else if (keycode == KEY_A)
        player->key_left = false;
    else if (keycode == KEY_D)
        player->key_right = false;
    else if (keycode == KEY_LEFT)
        player->key_rotate_left = false;
    else if (keycode == KEY_RIGHT)
        player->key_rotate_right = false;
    return (0);
}

bool check_collision_smooth(float new_x, float new_y, t_execution *execution)
{
    float margin;
    
    margin = PLAYER_SIZE;
    if (touch(new_x - margin, new_y - margin, execution) ||
        touch(new_x + margin, new_y - margin, execution) ||
        touch(new_x - margin, new_y + margin, execution) ||
        touch(new_x + margin, new_y + margin, execution))
        return (true);
    return (false);
}

bool check_collision(float new_x, float new_y, t_execution *execution)
{
    float margin;
    
    margin = PLAYER_SIZE;
    if (touch(new_x - margin, new_y - margin, execution) ||
        touch(new_x + margin, new_y - margin, execution) ||
        touch(new_x - margin, new_y + margin, execution) ||
        touch(new_x + margin, new_y + margin, execution))
        return (true);
    return (false);
}


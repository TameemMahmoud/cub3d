/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:58:25 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/10 12:04:46 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"

void init_player_keys(t_player *player)
{
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    player->key_rotate_left = false;
    player->key_rotate_right = false;
}

void init_player_angles(t_player *player, char player_dir)
{
    if (player_dir == 'N')
        player->angle = 3 * PI / 2;
    else if (player_dir == 'S')
        player->angle = PI / 2;
    else if (player_dir == 'E')
        player->angle = 0;
    else if (player_dir == 'W')
        player->angle = PI;
}

void ft_init_player(t_player *player, t_src *src)
{
    {
        player->x = src->map->player_x * BLOCK_SIZE + BLOCK_SIZE / 2;
        player->y = src->map->player_y * BLOCK_SIZE + BLOCK_SIZE / 2;
        init_player_angles(player, src->map->player_dir);
        init_player_keys(player);
    }
}
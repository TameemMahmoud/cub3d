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

void ft_init_player(t_player *player, t_src *src)
{
    player->x = src->map->player_x * BLOCK_SIZE + BLOCK_SIZE / 2;
    player->y = src->map->player_y * BLOCK_SIZE + BLOCK_SIZE / 2;
    
    if (src->map->player_dir == 'N')
        player->angle = 3 * PI / 2;  // Facing North (up)
    else if (src->map->player_dir == 'S')
        player->angle = PI / 2;      // Facing South (down)
    else if (src->map->player_dir == 'E')
        player->angle = 0;           // Facing East (right)
    else if (src->map->player_dir == 'W')
        player->angle = PI;          // Facing West (left)
    
    printf("Player initialized at grid (%d,%d) facing '%c'\n", 
           src->map->player_x, src->map->player_y, src->map->player_dir);
    printf("Pixel position: (%.1f, %.1f), angle: %.2f\n", 
           player->x, player->y, player->angle);
    
    init_player_keys(player);
}

int key_press(int keycode, t_player *player)
{
    printf("Key pressed: %d\n", keycode); // Debug output
    if(keycode == W)
        player->key_up = true;
    else if(keycode == S)
        player->key_down = true;
    else if(keycode == A)
        player->key_left = true;
    else if(keycode == D)
        player->key_right = true;
    else if(keycode == LEFT)
    {
        player->key_rotate_left = true;
        printf("Rotating left\n"); // Debug output
    }
    else if(keycode == RIGHT)
    {
        player->key_rotate_right = true;
        printf("Rotating right\n"); // Debug output
    }
    else if(keycode == ESC)
    {
        printf("Exiting game...\n"); // Debug output
        exit(0); // Exit the game when ESC is pressed
    }
    else
        printf("Unhandled key: %d\n", keycode); // Debug output for unhandled keys
    return (0);
}

int key_release(int keycode, t_player *player)
{
    printf("Key released: %d\n", keycode); // Debug output
    if(keycode == W)
        player->key_up = false;
    else if(keycode == S)
        player->key_down = false;
    else if(keycode == A)
        player->key_left = false;
    else if(keycode == D)
        player->key_right = false;
    else if(keycode == LEFT)
        player->key_rotate_left = false;
    else if(keycode == RIGHT)
        player->key_rotate_right = false;
    return (0);
}

void player_movement(t_player *player)
{
    player->cos_angle = cos(player->angle);
    player->sin_angle = sin(player->angle);

    
    if (player->key_rotate_left)
        player->angle -= ANGLE_SPEED;
    if (player->key_rotate_right)
        player->angle += ANGLE_SPEED;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI; 

    if (player->key_up)
    {
        player->x += player->cos_angle * PLAYER_SPEED;
        player->y += player->sin_angle * PLAYER_SPEED;
    }
    if (player->key_down)
    {
        player->x -= player->cos_angle * PLAYER_SPEED;
        player->y -= player->sin_angle * PLAYER_SPEED;
    }
    if (player->key_left)
    {
        player->x += player->sin_angle * PLAYER_SPEED;
        player->y -= player->cos_angle * PLAYER_SPEED;
    }
    if (player->key_right)
    {
        player->x -= player->sin_angle * PLAYER_SPEED;
        player->y += player->cos_angle * PLAYER_SPEED;
    }
}
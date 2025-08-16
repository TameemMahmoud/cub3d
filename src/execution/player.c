#include "execution.h"

void init_player(t_player *player)
{
    player->x = WIDTH / 2; // Start in the middle of the screen
    player->y = HEIGHT / 2; // Start in the middle of the screen
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
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
    return (0);
}

void player_movement(t_player *player)
{
    if (player->key_up)
        player->y -= PLAYER_SPEED; //up
    if (player->key_down)
        player->y += PLAYER_SPEED; //down
    if (player->key_left)
        player->x -= PLAYER_SPEED; //left
    if (player->key_right)
        player->x += PLAYER_SPEED; //right
}
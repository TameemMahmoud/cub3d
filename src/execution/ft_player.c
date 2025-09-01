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
        player->angle = 3 * PI / 2;
    else if (src->map->player_dir == 'S')
        player->angle = PI / 2;
    else if (src->map->player_dir == 'E')
        player->angle = 0;
    else if (src->map->player_dir == 'W')
        player->angle = PI;
    
    printf("Player initialized at grid (%d,%d) facing '%c'\n", 
           src->map->player_x, src->map->player_y, src->map->player_dir);
    printf("Pixel position: (%.1f, %.1f), angle: %.2f\n", 
           player->x, player->y, player->angle);
    printf("Platform detected: %s\n", PLATFORM_NAME);
    printf("Key mappings - W:%d A:%d S:%d D:%d ESC:%d\n", 
           KEY_W, KEY_A, KEY_S, KEY_D, KEY_ESC);
    
    init_player_keys(player);
}

int key_press(int keycode, t_player *player)
{
    printf("Key pressed: %d (%s)\n", keycode, PLATFORM_NAME); // Debug output with platform
    if(keycode == KEY_W)
        player->key_up = true;
    else if(keycode == KEY_S)
        player->key_down = true;
    else if(keycode == KEY_A)
        player->key_left = true;
    else if(keycode == KEY_D)
        player->key_right = true;
    else if(keycode == KEY_LEFT)
    {
        player->key_rotate_left = true;
        printf("Rotating left\n"); // Debug output
    }
    else if(keycode == KEY_RIGHT)
    {
        player->key_rotate_right = true;
        printf("Rotating right\n"); // Debug output
    }
    else if(keycode == KEY_ESC)
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
    printf("Key released: %d (%s)\n", keycode, PLATFORM_NAME); // Debug output with platform
    if(keycode == KEY_W)
        player->key_up = false;
    else if(keycode == KEY_S)
        player->key_down = false;
    else if(keycode == KEY_A)
        player->key_left = false;
    else if(keycode == KEY_D)
        player->key_right = false;
    else if(keycode == KEY_LEFT)
        player->key_rotate_left = false;
    else if(keycode == KEY_RIGHT)
        player->key_rotate_right = false;
    return (0);
}

void init_player_angles(t_player *player)
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
}
void set_key_left_and_right(t_player *player, t_execution *execution)
{
    if (player->key_left)
    {
        player->new_x = player->x + player->sin_angle * PLAYER_SPEED;
        player->new_y = player->y - player->cos_angle * PLAYER_SPEED;
        if (!touch(player->new_x, player->new_y, execution))
        {
            player->x = player->new_x;;
            player->y = player->new_y;
        }
    }
    if (player->key_right)
    {
        player->new_x = player->x - player->sin_angle * PLAYER_SPEED;
        player->new_y = player->y + player->cos_angle * PLAYER_SPEED;
        if (!touch(player->new_x, player->new_y, execution))
        {
            player->x = player->new_x;;
            player->y = player->new_y;
        }
    }
}

void set_key_up_and_down(t_player *player, t_execution *execution)
{
    if (player->key_up)
    {
        player->new_x = player->x + player->cos_angle * PLAYER_SPEED;
        player->new_y = player->y + player->sin_angle * PLAYER_SPEED;
        if (!touch(player->new_x, player->new_y, execution))
        {
            player->x = player->new_x;;
            player->y = player->new_y;
        }
    }
    if (player->key_down)
    {
        player->new_x = player->x - player->cos_angle * PLAYER_SPEED;
        player->new_y = player->y - player->sin_angle * PLAYER_SPEED;
        if (!touch(player->new_x, player->new_y, execution))
        {
            player->x = player->new_x;;
            player->y = player->new_y;
        }
    }
}

void ft_player_movement(t_player *player, t_execution *execution)
{   
    init_player_angles(player);
    set_key_up_and_down(player, execution);
    set_key_left_and_right(player, execution);
}

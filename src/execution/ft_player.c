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
    player->x = src->map->player_x * BLOCK_SIZE + BLOCK_SIZE / 2;
    player->y = src->map->player_y * BLOCK_SIZE + BLOCK_SIZE / 2;
    init_player_angles(player, src->map->player_dir);
    init_player_keys(player);
}

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

void move_with_sliding(t_player *player, t_execution *execution, 
                      float move_x, float move_y)
{
    float new_x;
    float new_y;
    
    new_x = player->x + move_x;
    new_y = player->y + move_y;
    
    if (!check_collision_smooth(new_x, new_y, execution))
    {
        player->x = new_x;
        player->y = new_y;
        return;
    }
    else if (!check_collision_smooth(new_x, player->y, execution))
    {
        player->x = new_x;
        return;
    }
    else if (!check_collision_smooth(player->x, new_y, execution))
    {
        player->y = new_y;
        return;
    }
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


void move_forward_backward(t_player *player, t_execution *execution)
{
    float move_x;
    float move_y;
    
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

void move_left_right(t_player *player, t_execution *execution)
{
    float move_x;
    float move_y;
    
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

void ft_player_movement(t_player *player, t_execution *execution)
{
    if (player->key_rotate_left)
        player->angle -= ANGLE_SPEED;
    else if (player->key_rotate_right)
        player->angle += ANGLE_SPEED;
    move_forward_backward(player, execution);
    move_left_right(player, execution);
}

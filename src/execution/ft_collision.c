#include "execution.h"

// Check if a position has collision with walls
bool check_wall_collision(float x, float y, t_execution *execution)
{
    int grid_x = (int)(x / BLOCK_SIZE);
    int grid_y = (int)(y / BLOCK_SIZE);

    // Bounds checking
    if (grid_y < 0 || grid_x < 0)
        return true;
    
    if (!execution->map || !execution->map[grid_y])
        return true;
    
    if (execution->map[grid_y][grid_x] == '\0')
        return true;

    // Check if it's a wall
    if (execution->map[grid_y][grid_x] == '1')
        return true;
    
    return false;
}

// Check collision with a small buffer around the player
bool check_player_collision(float new_x, float new_y, t_execution *execution)
{
    float buffer = PLAYER_SIZE / 2.0f; // Half player size as buffer
    
    // Check collision at player center and corners
    if (check_wall_collision(new_x, new_y, execution) ||
        check_wall_collision(new_x - buffer, new_y - buffer, execution) ||
        check_wall_collision(new_x + buffer, new_y - buffer, execution) ||
        check_wall_collision(new_x - buffer, new_y + buffer, execution) ||
        check_wall_collision(new_x + buffer, new_y + buffer, execution))
        return true;
    
    return false;
}

// Safe movement function - only moves if no collision
void move_player_safe(t_player *player, float new_x, float new_y, t_execution *execution)
{
    // Check X movement separately
    if (!check_player_collision(new_x, player->y, execution))
        player->x = new_x;
    
    // Check Y movement separately 
    if (!check_player_collision(player->x, new_y, execution))
        player->y = new_y;
}

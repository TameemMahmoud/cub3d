#include "../includes/cub3d.h"

static void init_structs(t_src *src, t_file *file)
{
    file->file_len = 0;
    file->file_map = NULL;
    file->map_start_index = 0;
    
    src->textures.north = NULL;
    src->textures.south = NULL;
    src->textures.west = NULL;
    src->textures.east = NULL;
    
    src->colors.floor_set = 0;
    src->colors.ceiling_set = 0;
}

static void init_malloc(t_src *src)
{
    src->mlx_ptr = NULL;
    src->win_ptr = NULL;
    src->map = NULL;
}

void init(t_src *src)
{
    init_malloc(src);
    init_structs(src, &src->file);
}
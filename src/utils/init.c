#include "includes/cub3d.h"


static void    init_malloc(t_src *src)
{
    src->mlx_ptr = NULL;
    src->win_ptr = NULL;
    src->map = (t_map *)ft_calloc(1, sizeof(t_map));
}

void init(t_src *src, char *file)
{
    
}
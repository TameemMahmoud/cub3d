#include "cub3d.h"
#include "execution.h"
#include "includes/libft/libft.h"

void cub3d(char *file)
{
    t_src   src;
    int		len;

    len = ft_strlen(file);
    if ((len - 4) <= 0 || ft_strncmp(".cub", file + (len - 4), len))
    {
        printf(INVALID_EXTENSION);
        exit(EXIT_FAILURE);
    }
    init(&src);
    parsing(&src, file);
    execution(&src);
}
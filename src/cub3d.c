#include "includes/cub3d.h"

void cub3d(char *file)
{
    t_src   src;
    int		len;

    len = ft_strlen(file);
    if ((len - 4) <= 0 || ft_strcmp(".cub", file + (len - 4)))
		exit_failure(INVALID_FILE_NAME);
    init(&src, file);
}
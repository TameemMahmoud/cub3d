#include "includes/cub3d.h"

int main(int ac, char **av)
{
    if(ac == 2)
        cub3d(av[1]);
    else
        exit_failure("Invalid arguments");
    return (0);
}

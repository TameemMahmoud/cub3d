#include "includes/cub3d.h"

int main(int ac, char **av)
{
    if(ac == 2)
        cub3d();
    else
    {
        printf("Invalid arguments\n");
        exit(EXIT_FAILURE);
    }
    return (0);
}
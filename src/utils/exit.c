#include "../includes/cub3d.h"

void	exit_failure_clear(t_src *src, char *err_msg)
{
	// TODO: clean
	if (*err_msg)
		printf(2, "%s\n", err_msg);
	exit(EXIT_FAILURE);
}


void	exit_failure(char *err_msg)
{
	if (*err_msg)
		printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}

int	exit_success(t_src *src)
{
	// TODO: clean before exit
	exit(EXIT_SUCCESS);
	return (0);
}
#include "../includes/cub3d.h"

void	exit_failure_clear(t_src *src, char *err_msg)
{
	(void) *src;
	/// TODO: clean
	if (*err_msg)
		printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}


void	exit_failure(char *err_msg)
{
	if (*err_msg)
		printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}

// int	exit_success(t_src *src)
// {
	
// 	exit(EXIT_SUCCESS);
// 	return (0);
// }
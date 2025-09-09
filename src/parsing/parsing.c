/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:39:41 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/08/11 14:07:19 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_parsing_summary(t_src *src)
{
	int	i;

	printf("=== PARSING SUMMARY ===\n");
	printf("Textures:\n");
	printf("  North: %s\n", src->textures.north);
	printf("  South: %s\n", src->textures.south);
	printf("  West:  %s\n", src->textures.west);
	printf("  East:  %s\n", src->textures.east);
	printf("\nColors:\n");
	printf("  Floor:   R=%d, G=%d, B=%d\n",
		src->colors.floor_r, src->colors.floor_g, src->colors.floor_b);
	printf("  Ceiling: R=%d, G=%d, B=%d\n",
		src->colors.ceiling_r, src->colors.ceiling_g, src->colors.ceiling_b);
	printf("\nMap:\n");
	printf("  Dimensions: %dx%d\n", src->map->width, src->map->height);
	printf("  Player: (%d, %d) facing %c\n",
		src->map->player_x, src->map->player_y, src->map->player_dir);
	printf("  Map grid:\n");
	i = 0;
	while (i < src->map->height)
	{
		printf("    %s\n", src->map->grid[i]);
		i++;
	}
	printf("======================\n\n");
}

static void	file_len(t_src *src, char *input_file)
{
	int		fd;
	char	*line;

	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		exit_failure_clear(src, INVALID_FD);
	while (1)
	{
		line = get_next_line(fd, 0);
		if (line == NULL)
			break ;
		src->file.file_len++;
		free(line);
	}
	close(fd);
	if (!src->file.file_len)
		exit_failure_clear(src, "Error\nInvalid: File Empty");
	if (src->file.file_len < 9)
		exit_failure_clear(src, "Error\nInvalid: File not complete");
}

static void	file_creation(t_src *src, t_file *file, char *input_file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		exit_failure_clear(src, INVALID_FD);
	file->file_map = (char **)ft_calloc(file->file_len + 1, sizeof(char *));
	if (!file->file_map)
		exit_failure_clear(src, "ERROR\nMalloc error");
	while (1)
	{
		line = get_next_line(fd, 0);
		if (line == NULL)
			break ;
		file->file_map[i++] = line;
	}
	close(fd);
}

void	parsing(t_src *src, char *input_file)
{
	t_file	*file;

	file = &src->file;
	file_len(src, input_file);
	file_creation(src, file, input_file);
	parse_config_elements(src);
	parse_map(src);
	print_parsing_summary(src);
}

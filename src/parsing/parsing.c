/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:39:41 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 17:59:58 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

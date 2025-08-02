/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:41:37 by tmahmoud          #+#    #+#             */
/*   Updated: 2024/12/23 16:15:46 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*strjoin_free(char *bf, char *buffer)
{
	char	*result;

	result = ft_strjoin(bf, buffer);
	if (bf)
		free(bf);
	return (result);
}

char	*my_read(int fd, char *bf)
{
	char	*buffer;
	int		read_len;

	if (!bf)
		bf = ft_calloc(1, 1);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	read_len = 1;
	while (read_len > 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_len] = '\0';
		bf = strjoin_free(bf, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (bf);
}

char	*get_line_m(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	return (line);
}

char	*get_next(char *buffer)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	next_line = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	next_line = ft_calloc((ft_strlen(buffer) + 1) - i, sizeof(char));
	i++;
	while (buffer[i])
		next_line[j++] = buffer[i++];
	if (!next_line)
		free(next_line);
	free(buffer);
	return (next_line);
}

char	*get_next_line(int fd, int free_buffer)
{
	static char	*buffer;
	char		*line;

	if (free_buffer == 1)
	{
		free(buffer);
		return (NULL);
	}
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = my_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line_m(buffer);
	buffer = get_next(buffer);
	return (line);
}

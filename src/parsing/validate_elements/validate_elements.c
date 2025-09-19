/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:49:17 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/09/15 17:46:23 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_texture_identifier(char *line)
{
	if (!line)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

static int	is_color_identifier(char *line)
{
	if (!line)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static void	validate_config_elements(t_src *src)
{
	if (!src->textures.north || !src->textures.south
		|| !src->textures.west || !src->textures.east)
		exit_failure_clear(src, "Error\nMissing texture paths");
	if (!src->colors.floor_set || !src->colors.ceiling_set)
		exit_failure_clear(src, "Error\nMissing color configurations");
}

static void	process_config_parsing(t_src *src, int *i, int *config_count)
{
	while (*i < src->file.file_len && *config_count < 6)
	{
		if (is_empty_line(src->file.file_map[*i]))
		{
			(*i)++;
			continue ;
		}
		if (is_texture_identifier(src->file.file_map[*i]))
		{
			parse_texture(src, src->file.file_map[*i]);
			(*config_count)++;
		}
		else if (is_color_identifier(src->file.file_map[*i]))
		{
			parse_color(src, src->file.file_map[*i]);
			(*config_count)++;
		}
		else
		{
			if (*config_count < 6)
				exit_failure_clear(src, "Error\nMissing config elements");
			break ;
		}
		(*i)++;
	}
}

void	parse_config_elements(t_src *src)
{
	int	i;
	int	config_count;

	i = 0;
	config_count = 0;
	process_config_parsing(src, &i, &config_count);
	validate_config_elements(src);
	src->file.map_start_index = i;
}

/*
void debug_parse_config_elements(t_src *src)
{
    int i = 0;
    int config_count = 0;
    
    printf("=== DEBUG: File contents ===\n");
    printf("Total file length: %d\n", src->file.file_len);
    
    while (i < src->file.file_len)
    {
        printf("Line %d: '%s'\n", i, 
		src->file.file_map[i] ?
		src->file.file_map[i] : "NULL");
        i++;
    }
    
    printf("=== DEBUG: Parsing config ===\n");
    
    i = 0;
    while (i < src->file.file_len && config_count < 6)
    {
        printf("Processing line %d: '%s'\n", i, src->file.file_map[i]);
        
        if (is_empty_line(src->file.file_map[i]))
        {
            printf("  -> Empty line, skipping\n");
            i++;
            continue;
        }
        
        if (is_texture_identifier(src->file.file_map[i]))
        {
            printf("  -> Found texture identifier\n");
            parse_texture(src, src->file.file_map[i]);
            config_count++;
            printf("  -> Config count now: %d\n", config_count);
        }
        else if (is_color_identifier(src->file.file_map[i]))
        {
            printf("  -> Found color identifier\n");
            parse_color(src, src->file.file_map[i]);
            config_count++;
            printf("  -> Config count now: %d\n", config_count);
        }
        else
        {
            printf("  -> Unknown line type\n");
            if (config_count < 6)
                exit_failure_clear(src, "Error\nMissing configuration elements");
            break;
        }
        i++;
    }
    
    printf("=== DEBUG: Final state ===\n");
    printf("North: %s\n", src->textures.north ? src->textures.north : "NULL");
    printf("South: %s\n", src->textures.south ? src->textures.south : "NULL");
    printf("West: %s\n", src->textures.west ? src->textures.west : "NULL");
    printf("East: %s\n", src->textures.east ? src->textures.east : "NULL");
    
    validate_config_elements(src);
    src->file.map_start_index = i;
}
*/

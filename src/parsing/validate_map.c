#include "../includes/cub3d.h"


static int	is_texture_identifier(char *line)
{
	if (!line)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 ||
		ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 ||
		ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

static int	is_color_identifier(char *line)
{
	if (!line)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "F ", 2) == 0 ||
		ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	store_texture_path(t_src *src, char *id, char *path)
{
	if (ft_strncmp(id, "NO", 2) == 0)
	{
		if (src->textures.north)
			exit_failure_clear(src, "Error\nDuplicate NO texture");
		src->textures.north = ft_strdup(path);
		if (!src->textures.north)
			exit_failure_clear(src, "Error\nMalloc error");
	}
	else if (ft_strncmp(id, "SO", 2) == 0)
	{
		if (src->textures.south)
			exit_failure_clear(src, "Error\nDuplicate SO texture");
		src->textures.south = ft_strdup(path);
		if (!src->textures.south)
			exit_failure_clear(src, "Error\nMalloc error");
	}
	else if (ft_strncmp(id, "WE", 2) == 0)
	{
		if (src->textures.west)
			exit_failure_clear(src, "Error\nDuplicate WE texture");
		src->textures.west = ft_strdup(path);
		if (!src->textures.west)
			exit_failure_clear(src, "Error\nMalloc error");
	}
	else if (ft_strncmp(id, "EA", 2) == 0)
	{
		if (src->textures.east)
			exit_failure_clear(src, "Error\nDuplicate EA texture");
		src->textures.east = ft_strdup(path);
		if (!src->textures.east)
			exit_failure_clear(src, "Error\nMalloc error");
	}
}

static void	parse_texture(t_src *src, char *line)
{
	char	*identifier;
	char	*trimmed_line;

	while (*line == ' ' || *line == '\t')
		line++;
	identifier = ft_substr(line, 0, 2);
	if (!identifier)
		exit_failure_clear(src, "Error\nMalloc error");
	line += 3;
	while (*line == ' ' || *line == '\t')
		line++;
	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
	{
		free(identifier);
		exit_failure_clear(src, "Error\nMalloc error");
	}
	store_texture_path(src, identifier, trimmed_line);
	free(identifier);
	free(trimmed_line);
}

static int	validate_color_values(char **rgb)
{
	int	r;
	int	g;
	int	b;

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

static void	store_color_values(t_src *src, char *id, char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (ft_strncmp(id, "F", 1) == 0)
	{
		if (src->colors.floor_set)
			exit_failure_clear(src, "Error\nDuplicate floor color");
		src->colors.floor_r = r;
		src->colors.floor_g = g;
		src->colors.floor_b = b;
		src->colors.floor_set = 1;
	}
	else if (ft_strncmp(id, "C", 1) == 0)
	{
		if (src->colors.ceiling_set)
			exit_failure_clear(src, "Error\nDuplicate ceiling color");
		src->colors.ceiling_r = r;
		src->colors.ceiling_g = g;
		src->colors.ceiling_b = b;
		src->colors.ceiling_set = 1;
	}
}

static void	parse_color(t_src *src, char *line)
{
	char	*identifier;
	char	*color_str;
	char	**rgb_values;

	while (*line == ' ' || *line == '\t')
		line++;
	identifier = ft_substr(line, 0, 1);
	if (!identifier)
		exit_failure_clear(src, "Error\nMalloc error");
	line += 2;
	while (*line == ' ' || *line == '\t')
		line++;
	color_str = ft_strtrim(line, "\n");
	if (!color_str)
	{
		free(identifier);
		exit_failure_clear(src, "Error\nMalloc error");
	}
	rgb_values = ft_split(color_str, ',');
	if (!validate_color_values(rgb_values))
		exit_failure_clear(src, "Error\nInvalid color format");
	store_color_values(src, identifier, rgb_values);
	free(identifier);
	free(color_str);
	free_split(rgb_values);
}

static void	validate_config_elements(t_src *src)
{
	if (!src->textures.north || !src->textures.south ||
		!src->textures.west || !src->textures.east)
		exit_failure_clear(src, "Error\nMissing texture paths");
	if (!src->colors.floor_set || !src->colors.ceiling_set)
		exit_failure_clear(src, "Error\nMissing color configurations");
}

void	parse_config_elements(t_src *src)
{
	int	i;
	int	config_count;

	i = 0;
	config_count = 0;
	while (i < src->file.file_len && config_count < 6)
	{
		if (is_empty_line(src->file.file_map[i]))
		{
			i++;
			continue ;
		}
		if (is_texture_identifier(src->file.file_map[i]))
		{
			parse_texture(src, src->file.file_map[i]);
			config_count++;
		}
		else if (is_color_identifier(src->file.file_map[i]))
		{
			parse_color(src, src->file.file_map[i]);
			config_count++;
		}
		else
		{
			if (config_count < 6)
				exit_failure_clear(src, "Error\nMissing configuration elements");
			break ;
		}
		i++;
	}
	validate_config_elements(src);
	src->file.map_start_index = i;
}

void debug_parse_config_elements(t_src *src)
{
    int i = 0;
    int config_count = 0;
    
    printf("=== DEBUG: File contents ===\n");
    printf("Total file length: %d\n", src->file.file_len);
    
    while (i < src->file.file_len)
    {
        printf("Line %d: '%s'\n", i, src->file.file_map[i] ? src->file.file_map[i] : "NULL");
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
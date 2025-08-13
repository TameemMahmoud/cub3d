#include "cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || 
			c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	count_map_lines(t_src *src)
{
	int	i;
	int	count;

	i = src->file.map_start_index;
	count = 0;
	while (i < src->file.file_len)
	{
		if (!is_empty_line(src->file.file_map[i]))
			count++;
		i++;
	}
	return (count);
}

static int	get_map_width(char **map_lines, int height)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (i < height)
	{
		current_width = ft_strlen(map_lines[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

static void	find_player(t_src *src, char **map_lines, int height)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < height)
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (is_player_char(map_lines[i][j]))
			{
				if (player_count > 0)
					exit_failure_clear(src, "Error\nMultiple players found");
				src->map->player_x = j;
				src->map->player_y = i;
				src->map->player_dir = map_lines[i][j];
				map_lines[i][j] = '0';
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
		exit_failure_clear(src, "Error\nNo player found");
}

static void	validate_map_chars(t_src *src, char **map_lines, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (!is_valid_map_char(map_lines[i][j]))
				exit_failure_clear(src, "Error\nInvalid character in map");
			j++;
		}
		i++;
	}
}

static void	extract_map_lines(t_src *src, char ***map_lines, int *height)
{
	int	i;
	int	map_index;

	*height = count_map_lines(src);
	if (*height == 0)
		exit_failure_clear(src, "Error\nNo map found");
	*map_lines = (char **)ft_calloc(*height + 1, sizeof(char *));
	if (!*map_lines)
		exit_failure_clear(src, "Error\nMalloc error");
	i = src->file.map_start_index;
	map_index = 0;
	while (i < src->file.file_len)
	{
		if (!is_empty_line(src->file.file_map[i]))
		{
			(*map_lines)[map_index] = ft_strtrim(src->file.file_map[i], "\n");
			if (!(*map_lines)[map_index])
				exit_failure_clear(src, "Error\nMalloc error");
			map_index++;
		}
		i++;
	}
}

static char	get_map_char_at(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}

static int	is_walkable_space_enclosed(char **map, int x, int y, int height)
{
	int	directions[4][2];
	int	i;
	int	new_x;
	int	new_y;
	char	neighbor;

	directions[0][0] = 0; directions[0][1] = -1;
	directions[1][0] = 0; directions[1][1] = 1;
	directions[2][0] = -1; directions[2][1] = 0;
	directions[3][0] = 1; directions[3][1] = 0;
	i = 0;
	while (i < 4)
	{
		new_x = x + directions[i][0];
		new_y = y + directions[i][1];
		neighbor = get_map_char_at(map, new_x, new_y, height);
		if (neighbor == ' ')
			return (0);
		i++;
	}
	return (1);
}

static void	validate_map_walls(t_src *src, char **map_lines, int height, int width)
{
	int	i;
	int	j;

	i = 0;
    (void) width;
	while (i < height)
	{
		j = 0;
		while (j < (int)ft_strlen(map_lines[i]))
		{
			if (map_lines[i][j] == '0')
			{
				if (!is_walkable_space_enclosed(map_lines, j, i, height))
					exit_failure_clear(src, "Error\nMap not closed by walls");
			}
			j++;
		}
		i++;
	}
}

static void	allocate_map_structure(t_src *src)
{
	src->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!src->map)
		exit_failure_clear(src, "Error\nMalloc error");
}

void	parse_map(t_src *src)
{
	char	**map_lines;
	int		height;

	allocate_map_structure(src);
	extract_map_lines(src, &map_lines, &height);
	validate_map_chars(src, map_lines, height);
	find_player(src, map_lines, height);
	src->map->width = get_map_width(map_lines, height);
	src->map->height = height;
	src->map->grid = map_lines;
	validate_map_walls(src, map_lines, height, src->map->width);
}
NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = src/includes/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# macOS MiniLibX
MLX_DIR = src/includes/mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Linux MiniLibX
MLX_LINUX_DIR = src/includes/mlx_linux
MLX_LINUX_LIB = $(MLX_LINUX_DIR)/libmlx.a
MLX_LINUX_FLAGS = -L$(MLX_LINUX_DIR) -lmlx -lXext -lX11 -lm -lz

FSANITIZE_FLAGS = -fsanitize=address -g

GNL_DIR = src/includes/get_next_line
GNL_FILES = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_FILES:.c=.o)

SRC_MAIN = src/main.c

SRC_PARSING = src/parsing/parsing.c \
	src/parsing/parse_map/parsing_map.c \
	src/parsing/parse_map/parse_map_utils.c \
	src/parsing/parse_map/find_player.c \
	src/parsing/parse_map/extract_map_lines.c \
	src/parsing/parse_map/allocate_map_structure.c \
	src/parsing/parse_map/validate_map_chars.c \
	src/parsing/validate_elements/color_storage.c \
	src/parsing/validate_elements/color_utils.c \
	src/parsing/validate_elements/color_validation.c \
	src/parsing/validate_elements/parse_color.c \
	src/parsing/validate_elements/parse_texture_helper.c \
	src/parsing/validate_elements/parse_texture.c \
	src/parsing/validate_elements/validate_elements.c

SRC_EXECUTION = src/execution/ft_execution.c \
	src/execution/ft_drawing.c \
	src/execution/ft_player.c \
	src/execution/ft_player_movement.c \
	src/execution/ft_init_player.c \
	src/execution/ft_init_cub3d.c \
	src/execution/ft_textures.c \
	src/execution/ft_calculation.c

SRC_UTILS = src/utils/init.c \
	src/utils/clean_up.c \
	src/utils/exit.c \
	src/utils/mlx_utils.c \
	src/utils/is_empty_line.c

SRC = src/cub3d.c \
	$(SRC_PARSING) \
	$(SRC_EXECUTION) \
	$(SRC_UTILS)

OBJS = $(SRC:.c=.o)
OBJS_MAIN = $(SRC_MAIN:.c=.o)

# Default macOS build
all: $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(MLX_LINUX_LIB):
	make -C $(MLX_LINUX_DIR)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS) $(OBJS_MAIN) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_MAIN) $(GNL_OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

linux: $(LIBFT_LIB) $(MLX_LINUX_LIB) $(OBJS) $(OBJS_MAIN) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_MAIN) $(GNL_OBJS) $(LIBFT_LIB) $(MLX_LINUX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Isrc/includes -Isrc/includes/libft -Isrc/includes/get_next_line -c $< -o $@

# Clean targets (simple)
clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	make clean -C $(MLX_LINUX_DIR)
	$(RM) $(OBJS) $(OBJS_MAIN) $(GNL_OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

fsanitize: CFLAGS += $(FSANITIZE_FLAGS)
fsanitize: fclean linux

.PHONY: all linux clean fclean re fsanitize

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = src/includes/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = src/includes/mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

GNL_DIR = src/includes/get_next_line
GNL_FILES = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_FILES:.c=.o)

SRC_MAIN = src/main.c
SRC = src/cub3d.c src/utils/init.c src/utils/clean_up.c src/utils/exit.c src/parsing/parsing.c src/parsing/validate_elements/validate_elements.c \
	src/parsing/parse_map/parsing_map.c src/utils/is_empty_line.c src/parsing/validate_elements/parse_color.c \
	src/parsing/validate_elements/parse_texture.c src/parsing/validate_elements/parse_texture_helper.c \
	src/parsing/validate_elements/color_storage.c src/parsing/validate_elements/color_utils.c src/parsing/validate_elements/color_validation.c \
	src/parsing/parse_map/allocate_map_structure.c src/parsing/parse_map/extract_map_lines.c \
	src/parsing/parse_map/validate_map_chars.c src/parsing/parse_map/find_player.c src/parsing/parse_map/parse_map_utils.c

OBJS = $(SRC:.c=.o)
OBJS_MAIN = $(SRC_MAIN:.c=.o)

all: $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS) $(OBJS_MAIN) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_MAIN) $(GNL_OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx_mac -Isrc/includes/libft -Isrc/includes/get_next_line -c $< -o $@

clean_libft:
	make clean -C $(LIBFT_DIR)

clean_mlx:
	make clean -C $(MLX_DIR)

clean: clean_libft clean_mlx
	rm -f $(OBJS) $(OBJS_MAIN) $(GNL_OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re clean_libft clean_mlx
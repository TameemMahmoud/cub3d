NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = src/includes/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = src/includes/mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
FSANATIZE_FLAGS = -fsanitize=address -g

GNL_DIR = src/includes/get_next_line
GNL_FILES = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_FILES:.c=.o)

SRC_MAIN = src/main.c
SRC = src/cub3d.c src/utils/init.c src/utils/clean_and_exit.c src/utils/mlx_utils.c src/parsing/parsing.c src/parsing/validate_map.c \
	src/parsing/parsing_map.c src/utils/is_empty_line.c src/execution/ft_execution.c src/execution/ft_drawing.c src/execution/ft_player.c src/execution/ft_init_cub3d.c\

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
	$(CC) $(CFLAGS) -Imlx_mac -Isrc/includes -Isrc/includes/libft -Isrc/includes/get_next_line -c $< -o $@

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

fsanitize: CFLAGS += $(FSANATIZE_FLAGS)
fsanitize: re

.PHONY: all clean fclean re clean_libft clean_mlx
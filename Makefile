NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = src/includes/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = src/includes/mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

SRC_MAIN = src/main.c
SRC = src/cub3d.c  src/utils/init.c 

OBJS = $(SRC:.c=.o)
OBJS_MAIN = $(SRC_MAIN:.c=.o)

all: $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS) $(OBJS_MAIN)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_MAIN) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c $(LIBFT_LIB)
	$(CC) $(CFLAGS) -Imlx_mac -Isrc/includes/libft -c $< -o $@

clean_libft:
	make clean -C $(LIBFT_DIR)

clean_mlx:
	make clean -C $(MLX_DIR)

clean: clean_libft clean_mlx
	rm -f $(OBJS) $(OBJS_MAIN)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re clean_libft clean_mlx
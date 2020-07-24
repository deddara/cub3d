MLX_DIR = ./minilibx/
COMPILE_FLGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGl -framework AppKit
LBFT_DIR = ./libft/

.PHONY = all

all:
	gcc $(COMPILE_FLGS) -L$(MLX_DIR) -L$(LBFT_DIR) $(MLX_FLAGS) main.c
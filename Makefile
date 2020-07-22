MLX_DIR = ./minilibx/
COMPILE_FLGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGl -framework AppKit

.PHONY = all

all:
	gcc $(COMPILE_FLGS) -L$(MLX_DIR) $(MLX_FLAGS) main.c
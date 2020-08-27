# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/27 16:22:26 by deddara           #+#    #+#              #
#    Updated: 2020/08/27 13:28:33 by deddara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

GAME_PROG = game
KEY_CTRLS = key_controls

MLX_DIR = ./libraries/minilibx/
LBFT_DIR = ./libraries/libft/
OBJ_DIR = obj/
HDR_DIR = ./includes/
HEADERS = -I$(HDR_DIR) -I./libraries/libft/includes/ -I./libraries/minilibx/ -I./libraries/gnl
COMPILE_FLGS = $(HEADERS) -g -Wall -Wextra -Werror
MLX_FLAGS = -lmlx 
CC = gcc


.PHONY: all clean fclean re bonus

#GNL
GNL_DIR = libraries/gnl/
GNL_SRC = $(addprefix $(GNL_DIR), get_next_line get_next_line_utils)
GNL_SRC.O = $(addprefix $(OBJ_DIR), $(GNL_SRC:=.o))
#PARSER
PARS_DIR = map_parser/
PARS_SRC = $(addprefix $(PARS_DIR),map_parser map_line_parser params_parser params_utils rgb_parser \
 parser textures_parser utils error)
PARS_SRC.O = $(addprefix $(OBJ_DIR), $(PARS_SRC:=.o))
#ENGINE
ENGINE_DIR = engine/
ENGINE_SRC = $(addprefix $(ENGINE_DIR),ray_caster ray_caster_utils painter sprite_painter sprites draw_floor_cl make_scr)
ENGINE_SRC.O = $(addprefix $(OBJ_DIR), $(ENGINE_SRC:=.o))
#CONTROLS
CTRLS_DIR = key_controls/
CTRLS_SRC = $(addprefix $(CTRLS_DIR), $(KEY_CTRLS) step_n_dir key_controls_utils)
CTRLS_SRC.O = $(addprefix $(OBJ_DIR), $(CTRLS_SRC:=.o))

#main files
MAIN_SRC = $(GAME_PROG) main
MAIN_SRC.O = $(addprefix $(OBJ_DIR), $(MAIN_SRC:=.o))

all: $(OBJ_DIR) lft lx $(NAME)
	@cp ./libraries/minilibx/libmlx.dylib ./
	@echo "\033[32m[+] Make completed!\033[0m"

$(NAME): $(GNL_SRC.O) $(PARS_SRC.O) $(ENGINE_SRC.O) $(CTRLS_SRC.O) $(MAIN_SRC.O)
	$(CC) $(COMPILE_FLGS) -O2 $(GNL_SRC.O) $(PARS_SRC.O) $(CTRLS_SRC.O) $(ENGINE_SRC.O) $(MAIN_SRC.O) \
	-L$(LBFT_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/$(GNL_DIR) $(OBJ_DIR)/$(PARS_DIR) $(OBJ_DIR)/$(CTRLS_DIR) $(OBJ_DIR)/$(ENGINE_DIR)

.PHONY: lft
lft:
	@$(MAKE) -C $(LBFT_DIR) --no-print-directory --silent
	@echo  "\033[32m[+] Libft builded\033[0m"


.PHONY: lx
lx:
	@$(MAKE) -C $(MLX_DIR) --no-print-directory --silent
	@echo "\033[32m[+] Minilibx builded\033[0m"

$(GNL_SRC.O): $(OBJ_DIR)%.o: %.c 
	@$(CC) $(BONUS) $(COMPILE_FLGS) -O2 -c $< -o $@
$(PARS_SRC.O): $(OBJ_DIR)%.o: %.c 
	@$(CC) $(BONUS) $(COMPILE_FLGS) -O2 -c $< -o $@
$(ENGINE_SRC.O) : $(OBJ_DIR)%.o: %.c 
	@$(CC) $(BONUS) $(COMPILE_FLGS) -O2 -c $< -o $@
$(CTRLS_SRC.O) : $(OBJ_DIR)%.o: %.c 
	@$(CC) $(BONUS) $(COMPILE_FLGS) -O2 -c $< -o $@
$(MAIN_SRC.O) : $(OBJ_DIR)%.o: %.c
	@$(CC) $(BONUS) $(COMPILE_FLGS) -O2 -c $< -o $@

bonus:
	make BONUS="-D BONUS" GAME_PROG=game_bonus KEY_CTRLS=key_controls_bonus all

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -rf a.out.dSYM
	@rm libmlx.dylib

re: fclean libfclean all

.PHONY: libfclean

libfclean :
	@$(MAKE) -C $(LBFT_DIR) --no-print-directory fclean
	@$(MAKE) -C $(MLX_DIR) --no-print-directory clean

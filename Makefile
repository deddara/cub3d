# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/27 16:22:26 by deddara           #+#    #+#              #
#    Updated: 2020/08/04 19:56:12 by deddara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

MLX_DIR = ./libraries/minilibx/
LBFT_DIR = ./libraries/libft/
OBJ_DIR = obj/
HDR_DIR = ./includes/
HEADERS = -I$(HDR_DIR) -I./libraries/libft/includes/ -I./libraries/minilibx/ -I./libraries/gnl
COMPILE_FLGS = $(HEADERS) -g -Wall -Wextra 
MLX_FLAGS = -lmlx 
CC = gcc


.PHONY: all clean fclean re bonus

#GNL
GNL_DIR = libraries/gnl/
GNL_SRC = $(addprefix $(GNL_DIR), get_next_line get_next_line_utils)
GNL_SRC.O = $(addprefix $(OBJ_DIR), $(GNL_SRC:=.o))
#PARSER
PARS_DIR = map_parser/
PARS_SRC = $(addprefix $(PARS_DIR),map_parser map_line_parser parser utils)
PARS_SRC.O = $(addprefix $(OBJ_DIR), $(PARS_SRC:=.o))


.PHONY: all clean fclean re bonus

all: $(OBJ_DIR) $(NAME)
	@cp ./libraries/minilibx/libmlx.dylib ./
	@echo "\033[32m[+] Make completed!\033[0m"

$(NAME): $(GNL_SRC.O) $(PARS_SRC.O)
	@$(CC) $(COMPILE_FLGS) -O2 $(GNL_SRC.O) $(PARS_SRC.O) -L$(LBFT_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS) main.c

$(OBJ_DIR):
	@mkdir -p	$(OBJ_DIR)/$(GNL_DIR) $(OBJ_DIR)/$(PARS_DIR)

$(GNL_SRC.O): $(OBJ_DIR)%.o: %.c 
	@$(CC) $(COMPILE_FLGS) -O2 -c $< -o $@

$(PARS_SRC.O): $(OBJ_DIR)%.o: %.c 
	@$(CC) $(COMPILE_FLGS) -O2 -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -rf a.out.dSYM
	@rm libmlx.dylib

re: fclean all
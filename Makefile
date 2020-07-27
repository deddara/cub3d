# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/27 16:22:26 by deddara           #+#    #+#              #
#    Updated: 2020/07/27 17:48:36 by deddara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

MLX_DIR = ./libraries/minilibx/
LBFT_DIR = ./libraries/libft/
OBJ_DIR = obj/
HDR_DIR = includes/
HEADERS = -I$(HDR_DIR) -Ilibraries/libft/includes/ -Ilibraries/minilibx/ 
COMPILE_FLGS = $(HEADERS) -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGl -framework AppKit
CC = gcc


.PHONY: all clean fclean re bonus

#GNL
GNL_DIR = libraries/gnl/
GNL_SRC = $(addprefix $(GNL_DIR), get_next_line get_next_line_utils)
GNL_SRC.O = $(addprefix $(OBJ_DIR), $(GNL_SRC:=.o))
#PARSER
PARS_DIR = map_parser/
PARS_SRC = $(addprefix $(PARS_DIR),map_parser utils)
PARS_SRC.O = $(addprefix $(OBJ_DIR), $(PARS_SRC:=.o))


.PHONY: all clean fclean re bonus

all: $(OBJ_DIR) $(NAME)
	@echo "\033[32m[+] Make completed!\033[0m"

$(NAME): $(GNL_SRC.O) $(PARS_SRC.O)
	@$(CC) $(COMPILE_FLGS) $(GNL_SRC.O) $(PARS_SRC.O) -L$(MLX_DIR) -L$(LBFT_DIR) $(MLX_FLAGS) main.c
	@echo "\033[32m[+] Make completed!\033[0m"

$(OBJ_DIR):
	@mkdir -p	$(OBJ_DIR)/$(GNL_DIR) $(OBJ_DIR)/$(PARS_DIR)

$(GNL_SRC.O): $(OBJ_DIR)%.o: %.c 
	@$(CC) $(COMPILE_FLGS) -c $< -o $@

$(PARS_SRC.O): $(OBJ_DIR)%.o: %.c 
	@$(CC) $(COMPILE_FLGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
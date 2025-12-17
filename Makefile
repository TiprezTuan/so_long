# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 15:23:13 by ttiprez           #+#    #+#              #
#    Updated: 2025/12/17 16:58:14 by ttiprez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= so_long

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -g

MLX_DIR		= minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_DIR		= src
SRC			= main.c					\
			  init_game.c				\
			  parse_map.c				\
			  pathfinding.c				\
			  render_game.c				\
			  get_next_line.c			\
			  player_actions.c			\
			  error_management.c		\
			  get_next_line_utils.c		\
			  check_map_integrity.c		\

HEADER_DIR	= include
HEADER		= $(HEADER_DIR)/so_long.h $(HEADER_DIR)/get_next_line.h $(HEADER_DIR)/struct.h

OBJ_DIR		= obj
OBJ			= $(SRC:.c=.o)
OBJ			:= $(OBJ:%=$(OBJ_DIR)/%)

all: $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -I$(HEADER_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LIB) $(LIBFT) -lXext -lX11 -lm -o $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

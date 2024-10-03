NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
LIBFT = ./LIBFT/libft.a

SRC_DIR = ./src
GNL_DIR = ./gnl
INC_DIR = ./include
LIBFT_DIR = ./LIBFT
MAP_DIR = ./maps
LIBFTMLX = ./MLX
LIBFTAM = $(LIBFTMLX)/libmlx.a
LIBSMLX = -Lmlx -lmlx -framework OpenGL -framework AppKit
ERROR_FREE_DIR = $(SRC_DIR)/error_free
PARSING_DIR = $(SRC_DIR)/parsing
RAYCASTING_DIR = $(SRC_DIR)/raycasting

OBJS_DIR = ./objs

SRCS = main.c \
		$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c \
		$(ERROR_FREE_DIR)/error.c \
		$(ERROR_FREE_DIR)/memory.c \
		$(PARSING_DIR)/parsing.c \
		$(PARSING_DIR)/parsing1.c \
		$(PARSING_DIR)/parsing_2.c \
		$(PARSING_DIR)/parsing_map.c \
		$(PARSING_DIR)/utils.c \
		$(PARSING_DIR)/utils2.c \
		$(PARSING_DIR)/check_map.c \
		$(RAYCASTING_DIR)/add_texture_key.c \
		$(RAYCASTING_DIR)/create_floor_ceiling.c \
		$(RAYCASTING_DIR)/process_input.c \
		$(RAYCASTING_DIR)/raycast.c \
		$(RAYCASTING_DIR)/start.c \
		$(RAYCASTING_DIR)/process_input_rotate.c \
		$(RAYCASTING_DIR)/calculation_camera.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

INCLUDES = -I$(INC_DIR) -I$(GNL_DIR) -I$(LIBFT_DIR)

all: $(OBJS_DIR) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBSMLX) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)  # Создаём поддиректории, если их ещё нет
	$(CC) $(CFLAGS) $(INCLUDES) -Imlx -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBFTAM):
	@$(MAKE) -C $(LIBFTMLX)

clean:
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re


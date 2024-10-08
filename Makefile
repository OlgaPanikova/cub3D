NAME = cub3D
NAMEB = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -fsanitize=undefined -g
LIBFT = ./LIBFT/libft.a

SRC_DIR = ./src
SRC_B_DIR = ./srcb
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

ERROR_FREE_DIR_B = $(SRC_B_DIR)/error_free_b
PARSING_DIR_B = $(SRC_B_DIR)/parsing_b
RAYCASTING_DIR_B = $(SRC_B_DIR)/raycasting_b

OBJS_DIR = ./objs
OBJS_DIR_B = ./objsb

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

SRCS_B = main_bonus.c \
		$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c \
		$(ERROR_FREE_DIR_B)/error_bonus.c \
		$(ERROR_FREE_DIR_B)/memory_bonus.c \
		$(PARSING_DIR_B)/parsing_bonus.c \
		$(PARSING_DIR_B)/parsing1_bonus.c \
		$(PARSING_DIR_B)/parsing_2_bonus.c \
		$(PARSING_DIR_B)/parsing_map_bonus.c \
		$(PARSING_DIR_B)/utils_bonus.c \
		$(PARSING_DIR_B)/utils2_bonus.c \
		$(PARSING_DIR_B)/check_map_bonus.c \
		$(RAYCASTING_DIR_B)/add_texture_key_bonus.c \
		$(RAYCASTING_DIR_B)/create_floor_ceiling_bonus.c \
		$(RAYCASTING_DIR_B)/process_input_bonus.c \
		$(RAYCASTING_DIR_B)/raycast_bonus.c \
		$(RAYCASTING_DIR_B)/start_bonus.c \
		$(RAYCASTING_DIR_B)/process_input_rotate_bonus.c \
		$(RAYCASTING_DIR_B)/calculation_camera_bonus.c \
		$(RAYCASTING_DIR_B)/animal_bonus.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_B = $(SRCS_B:%.c=$(OBJS_DIR_B)/%.o)

INCLUDES = -I$(INC_DIR) -I$(GNL_DIR) -I$(LIBFT_DIR)

all: $(OBJS_DIR) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBSMLX) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -Imlx -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

bonus: $(OBJS_DIR_B) $(NAMEB)

$(NAMEB): $(OBJS_B) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_B) $(LIBSMLX) -L$(LIBFT_DIR) -lft -o $(NAMEB)

$(OBJS_DIR_B)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -Imlx -c $< -o $@

$(OBJS_DIR_B):
	mkdir -p $(OBJS_DIR_B)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBFTAM):
	@$(MAKE) -C $(LIBFTMLX)

clean:
	rm -rf $(OBJS_DIR) $(OBJS_DIR_B)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME) $(NAMEB)
	make fclean -C $(LIBFT_DIR)

re: fclean all

re_b: fclean bonus

.PHONY: all clean fclean re bonus


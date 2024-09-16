NAME = cub3D
#NAMEB = so_long_bonus
SRCDIR = src
OBJDIR = obj
#SRCBDIR = srcb
#OBJBDIR = objb
SRCS = $(addprefix $(SRCDIR)/, main.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
#SRCB = $(addprefix $(SRCBDIR)/, main_bonus.c check_map_bonus.c ft_free_bonus.c check_map_2_bonus.c flood_fill_bonus.c painting_map_bonus.c sprites_bonus.c game_end_bonus.c animal_bonus.c)
#OBJB = $(patsubst $(SRCBDIR)/%.c, $(OBJBDIR)/%.o, $(SRCB))
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./Libft
LIBFTA = $(LIBFT)/libft.a
#LIBGNL = ./get_next_line
#LIBGNLA = $(LIBGNL)/libgnl.a
LIBS = -L$(LIBFT) -lft #-L$(LIBGNL) -lgnl
LIBFTMLX = ./MLX
LIBFTAM = $(LIBFTMLX)/libmlx.a
# MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
LIBSMLX = -Lmlx -lmlx -framework OpenGL -framework AppKit
HEADER = $(SRCDIR)/cub3D.h
#HEADERB = $(SRCBDIR)/so_long_bonus.h

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS) $(LIBFTA) #$(LIBGNLA)
	$(CC) $(CFLAGS) -Imlx $(OBJS) $(LIBS) $(LIBSMLX) -o $(NAME)

$(LIBFTAM):
	@$(MAKE) -C $(LIBFTMLX)

$(LIBFTA):
	@$(MAKE) -C $(LIBFT)

#$(LIBGNLA):
#	@$(MAKE) -C $(LIBGNL)

#bonus: $(NAMEB)

#$(NAMEB): $(OBJB) $(LIBFTA) $(LIBGNLA)
#	$(CC) $(CFLAGS) -Imlx $(OBJB) $(LIBS) $(LIBSMLX) -o $(NAMEB)

#$(OBJBDIR)/%.o: $(SRCBDIR)/%.c $(HEADERB)
#	mkdir -p $(OBJBDIR)
#	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)
	@$(MAKE) -C $(LIBFT) clean
#	@$(MAKE) -C $(LIBGNL) clean

fclean: clean
	$(RM) $(NAME) $(NAMEB)
	@$(MAKE) -C $(LIBFT) fclean
#	@$(MAKE) -C $(LIBGNL) fclean

re: fclean all

.PHONY: all clean fclean re #bonus
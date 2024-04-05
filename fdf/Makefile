NAME = fdf

SRCS =	fdf.c					\
		init_scenery.c			\
		read_map.c				\
		read_map_utils.c		\
		create_grid.c			\
		image.c					\
		draw.c					\
		draw_utils.c			\
		shift_n_rotate.c		\
		hooks.c					\
		free_.c

laag_SRCS =	laag_basic.c		\
			laag_operations.c	\
			laag_product.c		\
			laag_quaternion.c 

OBJS = $(SRCS:.c=.o) $(laag_SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LIBFT = libft

LIBMLX = minilibx-linux

MLXFLAGS = -I$(LIBMLX) -L$(LIBMLX) -L/usr/lib -lmlx_Linux -lXext -lX11

FTFLAGS = -I$(LIBFT) -L$(LIBFT) -lft

all: $(NAME)

$(NAME): $(LIBMLX)/libmlx.a $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(FTFLAGS) -lm -o $@

$(LIBFT)/libft.a:
	@make -C libft complete

$(LIBMLX):
	@wget https://cdn.intra.42.fr/document/document/21328/minilibx-linux.tgz
	@tar -xpf minilibx-linux.tgz
	@rm minilibx-linux.tgz

$(LIBMLX)/libmlx.a: $(LIBMLX)
	@make -C minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT) -c $<

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT) clean
	make -C $(LIBMLX) clean

fclean: clean
	rm -rf $(NAME) $(LIBFT)/libft.a

del: fclean
	rm -rf $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re

NAME = fdf

SRCS = draw.c image.c read_map.c free_.c fdf.c

laag_SRCS =	laag_basic.c		\
			laag_operations.c	\
			laag_product.c		\
			laag_quaternion.c 

OBJS = $(SRCS:.c=.o) $(laag_SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = libft

LIBMLX = minilibx-linux

MLXFLAGS = -I$(LIBMLX) -L$(LIBMLX) -L/usr/lib -lmlx_Linux -lXext -lX11

FTFLAGS = -I$(LIBFT) -L$(LIBFT) -lft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(FTFLAGS) -lm -o $@

$(LIBFT)/libft.a:
	@make -C libft complete

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT) -c $<

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean: clean
	rm -rf $(NAME) $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re

NAME = fdf

SRCS = draw.c linalg.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft

LIBMLX = minilibx-linux

MLXFLAGS = -I$(LIBMLX) -L$(LIBMLX) -L/usr/lib -lmlx_Linux -lXext -lX11

FTFLAGS = -I$(LIBFT) -L$(LIBFT) -lft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(FTFLAGS) -lm -o $@

$(LIBFT)/libft.a:
	@make -C libft printf

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean: clean
	rm -rf $(NAME) $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re

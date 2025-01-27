CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lmlx -lXext -lX11

SRCS = so_long.c map.c coin_check.c get_next_line.c get_next_line_utils.c handle_keys.c helper_functions.c \
		ft_printf.c ft_printf_string.c ft_printf_char.c ft_putnbr_d.c check_maps.c extension.c
OBJS = $(SRCS:.c=.o)

NAME = so_long

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

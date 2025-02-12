NAME = fract-ol

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3

INCLUDES = -I./libmlx_linux -I./ft_printf
LIBX_FLAGS = -L./libmlx_linux -lmlx -lXext -lX11 -lm -lz

LIBFTPRINTF = ft_printf/libftprintf.a

SRC = src/main.c \
	  src/fractol.c \
	  src/events.c \
	  src/helper_mandelbrot.c \
	  src/helper_julia.c \
	  src/helper_burning_ship.c

OBJ = $(SRC:.c=.o)

all: submodules $(LIBFTPRINTF) $(NAME)

submodules:
	@git submodule update --init --recursive

$(LIBFTPRINTF):
	make -C ft_printf
	make -C libmlx_linux

$(NAME): $(OBJ) $(LIBFTPRINTF)
	$(CC) $(OBJ) $(LIBX_FLAGS) -L./ft_printf -lftprintf -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C ft_printf clean

fclean: clean
	rm -f $(NAME)
	make -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re submodules
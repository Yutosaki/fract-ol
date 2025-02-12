NAME = fractol
NAME_BONUS = fractol_bonus

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
	  src/libft.c

SRC_BONUS = src_bonus/main_bonus.c \
			src_bonus/fractol_bonus.c \
			src_bonus/events_bonus.c \
			src_bonus/helper_mandelbrot_bonus.c \
			src_bonus/helper_julia_bonus.c \
			src_bonus/helper_burning_ship_bonus.c \
			src_bonus/libft_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(LIBFTPRINTF) $(NAME)

$(LIBFTPRINTF):
	make -C ft_printf
	make -C libmlx_linux

$(NAME): $(OBJ) $(LIBFTPRINTF)
	@git submodule update --init --recursive
	$(CC) $(OBJ) $(LIBX_FLAGS) -L./ft_printf -lftprintf -o $(NAME)

bonus: $(LIBFTPRINTF) $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFTPRINTF)
	@git submodule update --init --recursive
	$(CC) $(OBJ_BONUS) $(LIBX_FLAGS) -L./ft_printf -lftprintf -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	make -C ft_printf clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	make -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re submodules bonus
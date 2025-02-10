NAME = fract-ol

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3

INCLUDES = -I./libmlx_linux
LIBX_FLAGS = -L./libmlx_linux -lmlx -lXext -lX11 -lm -lz

SRC = src/main.c \
	  src/fractol.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re
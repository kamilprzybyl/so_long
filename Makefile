FLAGS = -Wall -Wextra -Werror ./Libft/libft.a -L ./mlx -lmlx -framework OpenGL -framework AppKit
NAME = 	so_long
MLX = 	mlx/libmlx.a
LIBFT = Libft/libft.a
SRC = 	src/so_long.c \
		src/init.c \
		src/hooks.c \
		src/draw_map.c \
		src/utils/resize_image.c \
		src/utils/mouse.c \
		src/utils/put_pixel.c \
		src/utils/get_pixel.c \
		src/utils/num_of_rows.c \
		src/utils/find_character.c \
		src/utils/ft_strlen_without_newline.c \
		src/utils/is_dup.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

OBJ = 	$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc -c -Wall -Werror -Wextra -D BUFFER_SIZE=100 $^ -o $@

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	gcc $(FLAGS) $^ -o $@

$(MLX):
	make --directory=./mlx

$(LIBFT):
	make --directory=./Libft

clean:
	rm -fr $(OBJ)

fclean:
	make clean
	rm -fr $(NAME)

re: fclean all
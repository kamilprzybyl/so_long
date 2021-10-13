FLAGS = -Wall -Wextra -Werror ./Libft/libft.a -L ./mlx -lmlx -framework OpenGL -framework AppKit
NAME = 	so_long
MLX = mlx/libmlx.a
LIBFT = Libft/libft.a
SRC = 	so_long.c \
		init.c \
		hooks.c \
		draw_map.c \
		utils/resize_image.c \
		utils/mouse.c \
		utils/put_pixel.c \
		utils/get_pixel.c \
		utils/num_of_rows.c \
		utils/find_character.c \
		utils/ft_strlen_without_newline.c \
		utils/is_dup.c \
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
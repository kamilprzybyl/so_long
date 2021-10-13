#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../Libft/inc/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_img {
	void	*ptr_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_game
{
	t_img	img[5];
	char	*xpm[5];
	t_vars	vars;
	char	**map;
	int		points;
	int		moves;
}				t_game;

# define SURFACE "textures/surface.xpm"
# define WALL "textures/wall.xpm"
# define PLAYER "textures/player.xpm"
# define FOOD "textures/food.xpm"
# define EXIT "textures/exit.xpm"

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SIX 22
# define KEY_FIVE 23
# define KEY_NINE 25
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_ZERO 29
# define KEY_BRACE_R 30
# define KEY_O 31
# define KEY_U 32
# define KEY_BRACE_L 33
# define KEY_I 34
# define KEY_P 35
# define KEY_L 37
# define KEY_J 38
# define KEY_K 40
# define KEY_SEMI 41
# define KEY_N 45
# define KEY_M 46
# define KEY_TAB 48
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 0x35

void	init(t_game *game, char **argv, int fd);
int		draw_map(t_game *game);
int		resize_images(t_game *game);
void	put_pixel(t_img *data, int x, int y, int color);
int		get_pixel(t_img *data, int x, int y);
int		find_character(t_game *game, int *x, int *y, char character);
int		num_of_rows(char *file);
int		handle_mouse(int key, t_game *game);
int		key_hook(int keycode, t_game *game);
int		ft_strlen_without_newline(char *s);
int		is_dup(char **str, char c);

#endif
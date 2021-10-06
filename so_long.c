#include "so_long.h"

int	get_num_of_cols(char *file)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nBad file descriptor\n", 28);
		return (-1);
	}
	while (get_next_line(fd))
		i++;
	close(fd);
	return (i);
}

char	**read_map(int fd, char **argv)
{
	int		i;
	int		j;
	char 	*line;
	char	**arr;

	j = 0;
	arr = (char **)malloc(sizeof(char *) * get_num_of_cols(argv[1]));
	if (!arr)
		return (arr);
	while (1)
	{
		line = get_next_line(fd);
		// printf("line = %s\n", line);
		if (!line)
			break ;
		arr[j] = (char *)malloc(sizeof(char) * ft_strlen(line));
		if (!arr[j])
			return (NULL);
		i = -1;
		while (line[++i])
			 arr[j][i] = line[i];
		arr[j][i] = '\0';
		j++;
	}
	arr[j] = NULL;
	close(fd);
	return (arr);
}

void my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_pixel(t_image *data, int x, int y)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}


/*
** on error returns 1 input image is not freed else it will overwrite the old image
*/
int	resize_ptr_img(t_image *ptr_img, void  *mlx)
{
	t_image new;
	int		x;
	int		y;

	new.ptr_img = mlx_new_image(mlx, ptr_img->width / 2, ptr_img->height / 2);
	if (!new.ptr_img)
		return (1);
	new.addr = mlx_get_data_addr(new.ptr_img, &new.bits_per_pixel, &new.line_length, &new.endian);
	new.width = ptr_img->width / 2;
	new.endian = ptr_img->height / 2;
	x = 0;
	while (x < ptr_img->width)
	{
		y = 0;
		while (y < ptr_img->height)
		{
			my_mlx_pixel_put(&new, x / 2, y / 2, get_pixel(ptr_img, x, y));
			y++;
		}
		x++;
	}
	mlx_destroy_image(mlx, ptr_img->ptr_img);
	*ptr_img = new;
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	// if (keycode == KEY_W)
	// 	move_up();
	// if (keycode == KEY_A)
	// 	move_down();
	// if (keycode == KEY_S)
	// 	move_left();
	// if (keycode == KEY_D)
	// 	move_right();
	return (1);
}

int	load_images(t_game *game)
{
	game->images[0].ptr_img = mlx_xpm_file_to_image(game->vars.mlx, SURFACE, &(game->images[0].width), &(game->images[0].height));
	game->images[0].addr = mlx_get_data_addr(game->images[0].ptr_img, &game->images[0].bits_per_pixel, &game->images[0].line_length, &game->images[0].endian);
	resize_ptr_img(&(game->images[0]), game->vars.mlx);
	game->images[1].ptr_img = mlx_xpm_file_to_image(game->vars.mlx, WALL, &(game->images[1].width), &(game->images[1].height));
	game->images[1].addr = mlx_get_data_addr(game->images[1].ptr_img, &game->images[1].bits_per_pixel, &game->images[1].line_length, &game->images[1].endian);
	resize_ptr_img(&(game->images[1]), game->vars.mlx);
	game->images[2].ptr_img = mlx_xpm_file_to_image(game->vars.mlx, PLAYER, &(game->images[2].width), &(game->images[2].height));
	game->images[2].addr = mlx_get_data_addr(game->images[2].ptr_img, &game->images[2].bits_per_pixel, &game->images[2].line_length, &game->images[2].endian);
	resize_ptr_img(&(game->images[2]), game->vars.mlx);
	game->images[3].ptr_img = mlx_xpm_file_to_image(game->vars.mlx, FOOD, &(game->images[3].width), &(game->images[3].height));
	game->images[3].addr = mlx_get_data_addr(game->images[3].ptr_img, &game->images[3].bits_per_pixel, &game->images[3].line_length, &game->images[3].endian);
	resize_ptr_img(&(game->images[3]), game->vars.mlx);
	game->images[4].ptr_img = mlx_xpm_file_to_image(game->vars.mlx, EXIT, &(game->images[4].width), &(game->images[4].height));
	game->images[4].addr = mlx_get_data_addr(game->images[4].ptr_img, &game->images[4].bits_per_pixel, &game->images[4].line_length, &game->images[4].endian);
	resize_ptr_img(&(game->images[4]), game->vars.mlx);
	return (0);
}

int	draw_map(t_game *game, char **arr)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	y = 0;
	while (arr[i])
	{
		j = 0;
		x = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '1')
				mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->images[1].ptr_img, x, y);
			if (arr[i][j] == 'P')
				mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->images[2].ptr_img, x, y);
			else if (arr[i][j] == 'C')
				mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->images[3].ptr_img, x, y);
			else if (arr[i][j] == 'E')
				mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->images[4].ptr_img, x, y);
			x += game->images[1].width;
			j++;
		}
		i++;
		y += game->images[1].width;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_game	game;
	int		fd;
	char	**arr;

	if (argc != 2)
	{
		write(2, "Error\ninvalid number of arguments\n", 34);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nBad file descriptor\n", 28);
		return (-1);
	}
	game.vars.mlx = mlx_init();
	arr = read_map(fd, argv);
	// for (int i = 0; arr[i]; i++)
	// 	for (int j = 0; arr[i][j]; j++)
	// 		printf("%c", arr[i][j]);
	// printf("\n");
	load_images(&game);
	game.vars.win = mlx_new_window(game.vars.mlx, game.images[1].width * (ft_strlen(arr[0]) - 1), game.images[1].width * get_num_of_cols(argv[1]), "LOL IT WORKS");
	draw_map(&game, arr);
	mlx_key_hook(game.vars.win, key_hook, &game.vars);
	mlx_loop(game.vars.mlx);
	return (0);
}

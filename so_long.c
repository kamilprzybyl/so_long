#include "so_long.h"

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

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		// mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == KEY_T)
		mlx_string_put(vars->mlx, vars->win, 500, 500, 0xFFFFFF, "KAMIL IST EHRENMANN");
	return (printf("Hello from key_hook!\n"));
}

/* int	load_images(t_game *game)
{
	t_image image;

	image.ptr_img = mlx_xpm_file_to_image(game->vars.mlx, SURFACE, &image.width, &image.height);
	game->images[0] = image.ptr_img;
	image.ptr_img = mlx_xpm_file_to_image(game->vars.mlx, WALL, &image.width, &image.height);
	game->images[1] = image.ptr_img;
	image.ptr_img = mlx_xpm_file_to_image(game->vars.mlx, PLAYER, &image.width, &image.height);
	game->images[2] = image.ptr_img;
	image.ptr_img = mlx_xpm_file_to_image(game->vars.mlx, FOOD, &image.width, &image.height);
	game->images[3] = image.ptr_img;
	image.ptr_img = mlx_xpm_file_to_image(game->vars.mlx, EXIT, &image.width, &image.height);
	game->images[4] = image.ptr_img;
	return (0);
} */

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
	return (arr);
}

/* int	draw_map(t_game *game, int fd)
{
	int		i;
	char 	*line;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '0')
				mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->images[0], 900, 300);
			else if (line[i] == '1')
				mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->images[1], 100, 0);
			else if (line[i] == 'P')
				mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->images[2], 0, 600);
			else if (line[i] == 'C')
				mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->images[3], 100, 600);
			else if (line[i] == 'E')
				mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->images[4], 300, 600);
			i++;
		}
		line = get_next_line(fd);
	}
	return (0);
} */

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
	*ptr_img = new;
	return (0);
}

int main(int argc, char **argv)
{
	t_game	game;
	int		fd;

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
	close(fd);
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, 1920, 1080, "SO_LONG");
	//printf("test\n");
	
	// char **arr = read_map(fd, argv);
	// for (int i = 0; arr[i]; i++)
	// 	for (int j = 0; arr[i][j]; j++)
	// 		printf("%c", arr[i][j]);
	// printf("\n");
	//load_images(&game);
	// draw_map(&game, fd);

	game.images[0].ptr_img = mlx_xpm_file_to_image(game.vars.mlx, PLAYER, &(game.images[0].width), &(game.images[0].height));
	game.images[0].addr = mlx_get_data_addr(game.images[0].ptr_img, &game.images[0].bits_per_pixel, &game.images[0].line_length, &game.images[0].endian);
	printf("line_lenght = %d\n", game.images[0].line_length);
	resize_ptr_img(&(game.images[0]), game.vars.mlx);
	printf("width = %d\n", game.images[0].width);
	printf("height = %d\n", game.images[0].height);
	printf("bbp: %d\n", game.images[0].bits_per_pixel);
	mlx_put_image_to_window(game.vars.mlx, game.vars.win, game.images[0].ptr_img, 50, 50);
	//mlx_put_image_to_window(game.vars.mlx, game.vars.win, game.images[1], 200, 800);
	// // mlx_put_image_to_window(game.vars.mlx, game.vars.win, game.images[2], 900, 600);
	// // mlx_put_image_to_window(game.vars.mlx, game.vars.win, game.images[3], 800, 800);
	// // mlx_put_image_to_window(game.vars.mlx, game.vars.win, game.images[4], 800, 20);
	mlx_key_hook(game.vars.win, key_hook, &game.vars);
	mlx_loop(game.vars.mlx);
	return (0);
}

#include "../inc/so_long.h"

static int	load_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		game->img[i].ptr_img = mlx_xpm_file_to_image(game->vars.mlx,
				game->xpm[i], &(game->img[i].width), &(game->img[i].height));
		game->img[i].addr = mlx_get_data_addr(game->img[i].ptr_img,
				&game->img[i].bits_per_pixel, &game->img[i].line_len,
				&game->img[i].endian);
		i++;
	}
	return (0);
}

static char	**read_map(t_game *game, int fd, char **argv)
{
	int		j;
	char	*line;

	j = 0;
	game->map = (char **)malloc(sizeof(char *) * (num_of_rows(argv[1]) + 1));
	if (!game->map)
		return (game->map);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map[j] = line;
		j++;
	}
	game->map[j] = NULL;
	close(fd);
	return (game->map);
}

int	validate_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != '1' && game->map[i][j] != '0'
				&& game->map[i][j] != 'P' && game->map[i][j] != 'E'
				&& game->map[i][j] != 'C' && game->map[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	return (find_character(game, &i, &j, '1')
		&& find_character(game, &i, &j, '0')
		&& find_character(game, &i, &j, 'P')
		&& find_character(game, &i, &j, 'E')
		&& find_character(game, &i, &j, 'C'));
}

int	validate_map(t_game *game, char **argv)
{
	int		i;
	int		j;
	int		len;
	int		len2;
	int		rows;

	i = 0;
	rows = (num_of_rows(argv[1]) - 1);
	len = ft_strlen_without_newline(game->map[i]);
	while (game->map[i])
	{
		j = 0;
		len2 = ft_strlen_without_newline(game->map[i]);
		if (len2 != len)
			return (0);
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			if ((i == 0 || i == rows || (j == 0 || j == len2 - 1))
				&& game->map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (!is_dup(game->map, 'P') && validate_characters(game));
}

void	init(t_game *game, char **argv, int fd)
{
	game->vars.mlx = mlx_init();
	game->map = read_map(game, fd, argv);
	if (!validate_map(game, argv))
	{
		write(2, "Error\nInvalid map\n", 18);
		exit(1);
	}
	game->xpm[0] = SURFACE;
	game->xpm[1] = WALL;
	game->xpm[2] = PLAYER;
	game->xpm[3] = FOOD;
	game->xpm[4] = EXIT;
	game->points = 0;
	game->moves = 0;
	load_images(game);
	while ((game->img[1].width * (ft_strlen(game->map[0]) - 1) > 2560)
		|| (game->img[1].width * num_of_rows(argv[1])) > 1440)
		resize_images(game);
	game->vars.win = mlx_new_window(game->vars.mlx, game->img[1].width
			* (ft_strlen(game->map[0]) - 1), game->img[1].width
			* num_of_rows(argv[1]), "LOL IT WORKS");
}

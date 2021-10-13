#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if (argc != 2)
	{
		write(2, "Error\ninvalid number of arguments\n", 34);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nBad file descriptor\n", 28);
		exit(1);
	}
	init(&game, argv, fd);
	draw_map(&game);
	mlx_key_hook(game.vars.win, key_hook, &game);
	mlx_hook(game.vars.win, 17, 1L << 0, handle_mouse, &game);
	mlx_loop(game.vars.mlx);
	return (0);
}

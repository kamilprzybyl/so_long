#include "so_long.h"

static void	handle_key(t_game *game, int key)
{
	int	x;
	int	y;
	int	i;
	int	j;

	find_character(game, &x, &y, 'P');
	i = x;
	j = y;
	game->map[x][y] = '0';
	if (key == KEY_W)
		i -= 1;
	else if (key == KEY_S)
		i += 1;
	else if (key == KEY_A)
		j -= 1;
	else if (key == KEY_D)
		j += 1;
	if (game->map[i][j] == 'E')
		exit(0);
	if (game->map[i][j] != '1')
	{
		x = i;
		y = j;
	}
	game->map[x][y] = 'P';
}

int	key_hook(int keycode, t_game *game)
{
	int	x;
	int	y;
	int	i;
	int	j;

	mlx_clear_window(game->vars.mlx, game->vars.win);
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->vars.mlx, game->vars.win);
		exit(0);
	}
	else
	{
		find_character(game, &x, &y, 'P');
		handle_key(game, keycode);
		find_character(game, &i, &j, 'P');
		if (j != y || x != i)
			printf("moves = %d\n", ++game->moves);
	}
	draw_map(game);
	return (1);
}

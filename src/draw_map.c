#include "../inc/so_long.h"

void	put_texture(t_game *game, char character, int x, int y)
{
	if (character == '1')
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->img[1].ptr_img, x, y);
	else if (character == 'P')
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->img[2].ptr_img, x, y);
	else if (character == 'C')
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->img[3].ptr_img, x, y);
	else if (character == 'E')
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->img[4].ptr_img, x, y);
}

int	draw_map(t_game *game)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	y = 0;
	while (game->map[i])
	{
		j = 0;
		x = 0;
		while (game->map[i][j])
		{
			put_texture(game, game->map[i][j], x, y);
			x += game->img[1].width;
			j++;
		}
		i++;
		y += game->img[1].width;
	}
	return (0);
}

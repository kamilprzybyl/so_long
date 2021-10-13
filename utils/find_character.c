#include "../so_long.h"

int	find_character(t_game *game, int *x, int *y, char character)
{
	*x = 0;
	while (game->map[*x])
	{
		*y = 0;
		while (game->map[*x][*y])
		{
			if (game->map[*x][*y] == character)
				return (1);
			(*y)++;
		}
		(*x)++;
	}
	return (0);
}

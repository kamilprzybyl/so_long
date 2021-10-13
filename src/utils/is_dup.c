#include "../../inc/so_long.h"

int	is_dup(char **str, char c)
{
	int	i;
	int	j;
	int	state;

	state = 0;
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == c && state == 1)
				return (1);
			else if (str[i][j] == c)
				state = 1;
		}
	}
	return (0);
}

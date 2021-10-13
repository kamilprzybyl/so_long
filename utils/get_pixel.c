#include "../so_long.h"

int	get_pixel(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

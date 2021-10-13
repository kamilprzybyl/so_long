#include "../../inc/so_long.h"

static int	resize_ptr_img(t_img *ptr_img, void *mlx)
{
	t_img	new;
	int		x;
	int		y;

	new.ptr_img = mlx_new_image(mlx, ptr_img->width / 2, ptr_img->height / 2);
	if (!new.ptr_img)
		return (1);
	new.addr = mlx_get_data_addr(new.ptr_img, &new.bits_per_pixel,
			&new.line_len, &new.endian);
	new.width = ptr_img->width / 2;
	new.height = ptr_img->height / 2;
	x = 0;
	while (x < ptr_img->width)
	{
		y = -1;
		while (++y < ptr_img->height)
			put_pixel(&new, x / 2, y / 2, get_pixel(ptr_img, x, y));
		x++;
	}
	mlx_destroy_image(mlx, ptr_img->ptr_img);
	*ptr_img = new;
	return (0);
}

int	resize_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (resize_ptr_img(&(game->img[i]), game->vars.mlx) == 1)
		{
			free(&(game->img[i]));
			exit(1);
		}
		i++;
	}
	return (0);
}

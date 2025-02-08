#include "fractol.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

static void	put_pixel(char *data, int x, int y, int color, int size_line, int bpp)
{
	int index = y * size_line + x * (bpp / 8);
	*(int *)(data + index) = color;
}

void render_fractal(void *mlx, void *win)
{
	void	*img;
	char	*data;
	int		bpp, size_line, endian;
	int		x, y;
	int		max_iter = 100;
	double	scale = 4.0;
	double	offset_re = -2.0;
	double	offset_im = -2.0;

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			double c_re = x * (scale / WIDTH) + offset_re;
			double c_im = y * (scale / HEIGHT) + offset_im;
			double zx = 0, zy = 0;
			int iter = 0;
			while ((zx * zx + zy * zy) < 4 && iter < max_iter)
			{
				double tmp = zx * zx - zy * zy + c_re;
				zy = 2 * zx * zy + c_im;
				zx = tmp;
				iter++;
			}
			int color;
			if (iter == max_iter)
				color = 0x000000;
			else
				color = (iter * 0xFFFFFF) / max_iter;
			put_pixel(data, x, y, color, size_line, bpp);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_destroy_image(mlx, img);
}

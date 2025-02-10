#include "fractol.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

static void	put_pixel(char *data, int x, int y, int color, int size_line, int bpp)
{
	int index = y * size_line + x * (bpp / 8);
	*(int *)(data + index) = color;
}

void render_mandelbrot(t_env *env)
{
	void	*img;
	char	*data;
	int		bpp, size_line, endian;
	int		x, y, iter;
	int		color;
	double	c_re, c_im, zx, zy, tmp;

	img = mlx_new_image(env->mlx, WIDTH, HEIGHT); 
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c_re = x * (env->scale / WIDTH) + env->offset_re;
			c_im = y * (env->scale / HEIGHT) + env->offset_im;
			zx = 0;
			zy = 0;
			iter = 0;
			while ((zx * zx + zy * zy) < 4 && iter < env->max_iter)
			{
				tmp = zx * zx - zy * zy + c_re;
				zy = 2 * zx * zy + c_im;
				zx = tmp;
				iter++;
			}
			if (iter == env->max_iter)
				color = 0x000000;
			else
				color = (((iter * 0xFFFFFF) / env->max_iter) + env->color_offset) & 0xFFFFFF;
			put_pixel(data, x, y, color, size_line, bpp);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
	mlx_destroy_image(env->mlx, img);
}

void render_julia(t_env *env, t_julia *julia)
{
	void	*img;
	char	*data;
	int		bpp, size_line, endian;
	int		x, y, iter;
	int		color;
	double	zx, zy, tmp;

	img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			zx = x * (env->scale / WIDTH) + env->offset_re;
			zy = y * (env->scale / HEIGHT) + env->offset_im;
			iter = 0;
			while ((zx * zx + zy * zy) < 4 && iter < env->max_iter)
			{
				tmp = zx * zx - zy * zy + julia->c_re;
				zy = 2 * zx * zy + julia->c_im;
				zx = tmp;
				iter++;
			}
			if (iter == env->max_iter)
				color = 0x000000;
			else
				color = (((iter * 0xFFFFFF) / env->max_iter) + env->color_offset) & 0xFFFFFF;
			put_pixel(data, x, y, color, size_line, bpp);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
	mlx_destroy_image(env->mlx, img);
}

void render_burning_ship(t_env *env)
{
	void	*img;
	char	*data;
	int		bpp, size_line, endian;
	int		x, y, iter;
	int		color;
	double	c_re, c_im, zx, zy, tmp;

	img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c_re = x * (env->scale / WIDTH) + env->offset_re;
			c_im = y * (env->scale / HEIGHT) + env->offset_im;
			zx = 0;
			zy = 0;
			iter = 0;
			while ((zx * zx + zy * zy) < 4 && iter < env->max_iter)
			{
				tmp = zx * zx - zy * zy + c_re;
				zy = fabs(2 * zx * zy) + c_im;
				zx = fabs(tmp);
				iter++;
			}
			if (iter == env->max_iter)
				color = 0x000000;
			else
				color = (((iter * 0xFFFFFF) / env->max_iter) + env->color_offset) & 0xFFFFFF;
			put_pixel(data, x, y, color, size_line, bpp);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
	mlx_destroy_image(env->mlx, img);
}

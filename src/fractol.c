#include "fractol.h"

void	put_pixel(char *data, t_point p, int color, int size_line, int bpp)
{
	int	index;

	index = p.y * size_line + p.x * (bpp / 8);
	*(int *)(data + index) = color;
}

void	render_mandelbrot(t_env *env)
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;

	img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	render_mandelbrot_lines(env, data, size_line, bpp);
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
	mlx_destroy_image(env->mlx, img);
}

void	render_julia(t_env *env, t_julia *julia)
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;

	img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	render_julia_lines(env, julia, data, size_line, bpp);
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
	mlx_destroy_image(env->mlx, img);
}

void	render_burning_ship(t_env *env)
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;

	img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	render_burning_ship_lines(env, data, size_line, bpp);
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
	mlx_destroy_image(env->mlx, img);
}

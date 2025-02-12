#include "fractol.h"

int	calc_mandelbrot(double c_re, double c_im, t_env *env)
{
	int		iter;
	double	zx;
	double	zy;
	double	tmp;

	iter = 0;
	zx = 0;
	zy = 0;
	while ((zx * zx + zy * zy) < 4 && iter < MAX_ITER)
	{
		tmp = zx * zx - zy * zy + c_re;
		zy = 2 * zx * zy + c_im;
		zx = tmp;
		iter++;
	}
	if (iter == MAX_ITER)
		return (0x000000);
	return ((((iter * 0xFFFFFF) / MAX_ITER) + env->color_offset) & 0xFFFFFF);
}

void	render_mandelbrot_line(int y, t_env *env, char *data, int size_line,
		int bpp)
{
	t_point	p;
	int		color;
	double	c_re;
	double	c_im;

	p.y = y;
	p.x = 0;
	while (p.x < WIDTH)
	{
		c_re = p.x * (env->scale / WIDTH) + env->offset_re;
		c_im = p.y * (env->scale / HEIGHT) + env->offset_im;
		color = calc_mandelbrot(c_re, c_im, env);
		put_pixel(data, p, color, size_line, bpp);
		p.x++;
	}
}

void	render_mandelbrot_lines(t_env *env, char *data, int size_line, int bpp)
{
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		render_mandelbrot_line(y, env, data, size_line, bpp);
		y++;
	}
}

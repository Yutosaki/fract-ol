#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <ft_printf.h>

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITER 100
# define DEFAULT_SCALE 4.0
# define DEFAULT_OFFSET_RE -2.0
# define DEFAULT_OFFSET_IM -2.0
# define DEFAULT_COLOR_OFFSET 0

typedef enum e_fractal
{
	MANDELBROT,
	JULIA,
	BURNING_SHIP
}				t_fractal;

typedef struct s_env
{
	void*		mlx;
	void*		win;
	t_fractal	type;
	double		scale;
	double		offset_re;
	double		offset_im;
	int			color_offset;
}				t_env;

typedef struct s_julia
{
    double	c_re;
    double	c_im;
}				t_julia;

typedef struct s_all
{
	t_env	env;
	t_julia	julia;
}				t_all;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

static void put_pixel(char* data, t_point p, int color, int size_line, int bpp);

static int calc_mandelbrot(double c_re, double c_im, t_env* env);
static void render_mandelbrot_line(int y, t_env* env, char* data, int size_line, int bpp);
static void render_mandelbrot_lines(t_env* env, char* data, int size_line, int bpp);
void	render_mandelbrot(t_env* env);

static int calc_julia(double zx, double zy, t_julia* julia, t_env* env);
static void render_julia_line(int y, t_env* env, t_julia* julia, char* data, int size_line, int bpp);
static void render_julia_lines(t_env* env, t_julia* julia, char* data, int size_line, int bpp);
void	render_julia(t_env* env, t_julia* julia);

static int calc_burning_ship(double c_re, double c_im, t_env* env);
static void render_burning_ship_line(int y, t_env* env, char* data, int size_line, int bpp);
static void render_burning_ship_lines(t_env* env, char* data, int size_line, int bpp);
void	render_burning_ship(t_env* env);

void	render_fractal(t_all* all);


#endif // FRACTOL_H

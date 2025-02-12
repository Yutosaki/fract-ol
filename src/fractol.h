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

void	render_mandelbrot(t_env* env);
void	render_julia(t_env* env, t_julia* julia);
void	render_burning_ship(t_env* env);
void	render_fractal(t_all* all);


#endif // FRACTOL_H

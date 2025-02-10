#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITER 100

typedef enum e_fractal
{
	MANDELBROT,
	JULIA,
	BURNING_SHIP
}				t_fractal;

typedef struct s_env
{
	void		*mlx;
	void		*win;
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

void	render_fractal(t_all *all);
void	render_mandelbrot(t_env *env);
void	render_julia(t_env *env, t_julia *julia);
void	render_burning_ship(t_env *env);

#endif // FRACTOL_H

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 800
# define HEIGHT 600

typedef enum e_fractal
{
	MANDELBROT,
	JULIA
}				t_fractal;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	t_fractal	type;
	int			max_iter;
	double		scale;
	double		offset_re;
	double		offset_im;
	// Zoom などの今後のレンダリングオプションも追加可能
}				t_env;

typedef struct s_julia
{
    double	c_re;
    double	c_im;
}				t_julia;

void	render_fractal(t_env *env, t_julia *julia);
void	render_mandelbrot(t_env *env);
void	render_julia(t_env *env, t_julia *julia);

#endif // FRACTOL_H

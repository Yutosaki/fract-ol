/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:02:41 by yutsasak          #+#    #+#             */
/*   Updated: 2025/02/12 17:02:42 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include <ft_printf.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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
	double		c_re;
	double		c_im;
}				t_julia;

typedef struct s_all
{
	t_env		env;
	t_julia		julia;
}				t_all;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_img
{
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

void			set_env(t_all *all);

void			render_mandelbrot(t_env *env);
void			render_julia(t_env *env, t_julia *julia);
void			render_burning_ship(t_env *env);
void			render_fractal(t_all *all);

int				calc_mandelbrot(double c_re, double c_im, t_env *env);
void			render_mandelbrot_line(int y, t_env *env, t_img *img);
void			render_mandelbrot_lines(t_env *env, t_img *img);

int				calc_julia(double c_re, double c_im, t_julia *julia,
					t_env *env);
void			render_julia_line(int y, t_env *env, t_julia *julia,
					t_img *img);
void			render_julia_lines(t_env *env, t_julia *julia, t_img *img);

int				calc_burning_ship(double c_re, double c_im, t_env *env);
void			render_burning_ship_line(int y, t_env *env, t_img *img);
void			render_burning_ship_lines(t_env *env, t_img *img);

void			put_pixel(t_img *img, t_point p, int color);

#endif // FRACTOL_H

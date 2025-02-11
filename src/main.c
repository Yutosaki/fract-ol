#include <mlx.h>
#include <stdlib.h>
#include "fractol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ft_printf.h>

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

double	ft_atof(const char *str)
{
	double	res;
	double	sign;
	int		i;
	double	frac;
	double	power;

	res = 0.0;
	sign = 1.0;
	i = 0;
	frac = 0.0;
	power = 1.0;
	if (str[i] == '-')
	{ sign = -1.0; i++; }
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{ frac = frac * 10.0 + (str[i] - '0'); power *= 10.0; i++; }
		res = res + frac / power;
	}
	return (res * sign);
}

static void	print_usage(char *prog)
{
	ft_printf("Usage: %s [mandelbrot | julia <julia_c_re> <julia_c_im> | burning_ship]\n", prog);
	exit(1);
}

static void	init_fractal_type(int argc, char **argv, t_all *all)
{
	if (argc < 2 || argc > 4)
		print_usage(argv[0]);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		all->env.type = MANDELBROT;
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		all->env.type = JULIA;
		if (argc == 4)
		{
			all->julia.c_re = ft_atof(argv[2]);
			all->julia.c_im = ft_atof(argv[3]);
		}
		else
		{
			all->julia.c_re = -0.7;
			all->julia.c_im = 0.27015;
		}
	}
	else if (ft_strcmp(argv[1], "burning_ship") == 0)
		all->env.type = BURNING_SHIP;
	else
		print_usage(argv[0]);
}

int	handle_key(int keycode, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keycode == 65361) //left arrow
		all->env.offset_re -= all->env.scale * 0.1;
	else if (keycode == 65363) //right arrow
		all->env.offset_re += all->env.scale * 0.1;
	else if (keycode == 65362) // up arrow
		all->env.offset_im -= all->env.scale * 0.1;
	else if (keycode == 65364) // down arrow
		all->env.offset_im += all->env.scale * 0.1;
	else if (keycode == 99)  // c
		all->env.color_offset += 5000;
	else if (keycode == 118) // v
		all->env.color_offset -= 5000;
	else if (keycode == 65307) // esc
		exit(0);

	render_fractal(all);
	return (0);
}

int	handle_destroy(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_all	*all;
	double	old_scale;

	all = (t_all *)param;
	old_scale = all->env.scale;
	if (button == 4)
		all->env.scale *= 0.9;
	else if (button == 5)
		all->env.scale *= 1.1; 
	all->env.offset_re += (x * (old_scale - all->env.scale)) / WIDTH;
	all->env.offset_im += (y * (old_scale - all->env.scale)) / HEIGHT;

	render_fractal(all);
	return (0);
}

void render_fractal(t_all *all)
{
	if (all->env.type == MANDELBROT)
		render_mandelbrot(&all->env);
	else if (all->env.type == JULIA)
		render_julia(&all->env, &all->julia);
	else if (all->env.type == BURNING_SHIP)
		render_burning_ship(&all->env);
}

void set_env(t_all *all)
{
	all->env.scale = DEFAULT_SCALE;
	all->env.offset_re = DEFAULT_OFFSET_RE;
	all->env.offset_im = DEFAULT_OFFSET_IM;
	all->env.color_offset = DEFAULT_COLOR_OFFSET;
	all->env.mlx = mlx_init();
	all->env.win = mlx_new_window(all->env.mlx, WIDTH, HEIGHT, "fract-ol");
	render_fractal(all);
	mlx_hook(all->env.win, 17, 1L<<17, handle_destroy, NULL);
	mlx_key_hook(all->env.win, handle_key, all);
	mlx_mouse_hook(all->env.win, handle_mouse, all);
	mlx_loop(all->env.mlx);
}

int	main(int argc, char **argv)
{
	t_all	all;

	init_fractal_type(argc, argv, &all);
	set_env(&all);
	return (0);
}

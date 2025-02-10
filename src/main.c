#include <mlx.h>
#include <stdlib.h>
#include "fractol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	handle_key(int keycode, void *param)
{
	t_all *all = (t_all *)param;

	if (keycode == 65361)
		all->env.offset_re -= all->env.scale * 0.1;
	else if (keycode == 65363) 
		all->env.offset_re += all->env.scale * 0.1;
	else if (keycode == 65362) 
		all->env.offset_im -= all->env.scale * 0.1;
	else if (keycode == 65364) 
		all->env.offset_im += all->env.scale * 0.1;
	else if (keycode == 99)
		all->env.color_offset += 5000;
	else if (keycode == 118)
		all->env.color_offset -= 5000;
	else if (keycode == 65307) 
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

static void	print_usage(char *prog)
{
	printf("Usage: %s [mandelbrot | julia <julia_c_re> <julia_c_im> | burning_ship]\n", prog);
	exit(1);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_all *all = (t_all *)param;
	double old_scale = all->env.scale;
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

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc < 2 || argc > 4)
		print_usage(argv[0]);
	if (strcmp(argv[1], "mandelbrot") == 0)
		all.env.type = MANDELBROT;
	else if (strcmp(argv[1], "julia") == 0)
	{
		all.env.type = JULIA;
		if (argc == 4)
		{
			all.julia.c_re = atof(argv[2]);
			all.julia.c_im = atof(argv[3]);
		}
		else
		{
			all.julia.c_re = -0.7;
			all.julia.c_im = 0.27015;
		}
	}
	else if (strcmp(argv[1], "burning_ship") == 0)
	{
		all.env.type = BURNING_SHIP;
	}
	else
		print_usage(argv[0]);

	all.env.scale = 4.0;
	all.env.offset_re = -2.0;
	all.env.offset_im = -2.0;
	all.env.color_offset = 0;

	all.env.mlx = mlx_init();
	all.env.win = mlx_new_window(all.env.mlx, WIDTH, HEIGHT, "fract-ol");

	render_fractal(&all);

	mlx_hook(all.env.win, 17, 1L<<17, handle_destroy, NULL);
	mlx_key_hook(all.env.win, handle_key, &all);
	mlx_mouse_hook(all.env.win, handle_mouse, &all);
	mlx_loop(all.env.mlx);
	return (0);
}

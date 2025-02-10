#include <mlx.h>
#include <stdlib.h>
#include "fractol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	handle_key(int keycode, void *param)
{
	t_all *all = (t_all *)param;
	(void)all;
	printf("keycode: %d\n", keycode);
	if (keycode == 65307) // ESCキー
		exit(0);
	return (0);
}

int	handle_destroy(void *param)
{
	printf("destroy\n");
	(void)param;
	exit(0);
	return (0);
}

static void	print_usage(char *prog)
{
	printf("Usage: %s [mandelbrot | julia <julia_c_re> <julia_c_im>]\n", prog);
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
	else
		print_usage(argv[0]);

	all.env.max_iter = 100;
	all.env.scale = 4.0;
	all.env.offset_re = -2.0;
	all.env.offset_im = -2.0;

	all.env.mlx = mlx_init();
	all.env.win = mlx_new_window(all.env.mlx, WIDTH, HEIGHT, "fract-ol");

	render_fractal(&all);

	mlx_hook(all.env.win, 17, 1L<<17, handle_destroy, NULL);
	mlx_key_hook(all.env.win, handle_key, &all);
	mlx_mouse_hook(all.env.win, handle_mouse, &all);
	mlx_loop(all.env.mlx);
	return (0);
}

#include <mlx.h>
#include <stdlib.h>
#include "fractol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	handle_key(int keycode, void *param)
{
	t_env *env = (t_env *)param;
	printf("keycode: %d\n", keycode);
	(void)env;
	if (keycode == 65307) // ESCキー
		exit(0);
	// Zoom 機能などのキー処理を追加可能
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

void render_fractal(t_env *env, t_julia *julia)
{
	if (env->type == MANDELBROT)
		render_mandelbrot(env);
	else if (env->type == JULIA)
		render_julia(env, julia);
}

int	main(int argc, char **argv)
{	
	t_env	env;
	t_julia	julia;

	if (argc < 2 || argc > 4)
		print_usage(argv[0]);
	if (strcmp(argv[1], "mandelbrot") == 0)
		env.type = MANDELBROT;
	else if (strcmp(argv[1], "julia") == 0)
	{
		env.type = JULIA;
		if (argc == 4)
		{
			julia.c_re = atof(argv[2]);
			julia.c_im = atof(argv[3]);
		}
		else
		{
			julia.c_re = -0.7;
			julia.c_re = 0.27015;
		}
	}
	else
		print_usage(argv[0]);

	env.max_iter = 100;
	env.scale = 4.0;
	env.offset_re = -2.0;
	env.offset_im = -2.0;

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "fract-ol");

	render_fractal(&env, &julia);

	mlx_hook(env.win, 17, 1L<<17, handle_destroy, NULL);
	mlx_key_hook(env.win, handle_key, NULL);
	mlx_loop(env.mlx);
	return (0);
}

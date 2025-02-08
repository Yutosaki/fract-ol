#include <mlx.h>
#include <stdlib.h>
#include "fractol.h"
#include <stdio.h>

int	handle_key(int keycode, void *param)
{
    (void)param;
	printf("keycode: %d\n", keycode);
	if (keycode == 65307) // 校舎のものだと違うかも？
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

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;

    (void)argc;
	(void)argv;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "fract-ol");

	render_fractal(mlx, win);

	mlx_hook(win, 17, 1L<<17, handle_destroy, NULL);
	mlx_key_hook(win, handle_key, NULL);
	mlx_loop(mlx);
	return (0);
}

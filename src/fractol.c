#include "fractol.h"
#include <mlx.h>

void	render_fractal(void *mlx, void *win, int width, int height)
{
	mlx_pixel_put(mlx, win, width / 2, height / 2, 0xFFFFFF);
}

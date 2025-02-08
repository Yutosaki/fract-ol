#include "fractol.h"
#include <mlx.h>
#include <math.h>

void render_fractal(void *mlx, void *win)
{
	int x, y;
	int max_iter = 100;
	double scale = 4.0;         // 描画範囲（実数部・虚数部）の幅
	double offset_re = -2.0;      // 実数部のオフセット
	double offset_im = -2.0;      // 虚数部のオフセット

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			double c_re = x * (scale / WIDTH) + offset_re;
			double c_im = y * (scale / HEIGHT) + offset_im;
			double zx = 0, zy = 0;
			int iter = 0;
			while ((zx * zx + zy * zy) < 4 && iter < max_iter)
			{
				double tmp = zx * zx - zy * zy + c_re;
				zy = 2 * zx * zy + c_im;
				zx = tmp;
				iter++;
			}
			int color;
			if (iter == max_iter)
				color = 0x000000; // 黒：発散せず
			else
				color = (iter * 0xFFFFFF) / max_iter; // 発散する場合、グレースケールで色を設定
			mlx_pixel_put(mlx, win, x, y, color);
			x++;
		}
		y++;
	}
}

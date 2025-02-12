/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:02:36 by yutsasak          #+#    #+#             */
/*   Updated: 2025/02/12 17:02:37 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	handle_key(int keycode, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keycode == 65361)
		all->env.offset_re = all->env.offset_re - all->env.scale * 0.1;
	else if (keycode == 65363)
		all->env.offset_re = all->env.offset_re + all->env.scale * 0.1;
	else if (keycode == 65362)
		all->env.offset_im = all->env.offset_im - all->env.scale * 0.1;
	else if (keycode == 65364)
		all->env.offset_im = all->env.offset_im + all->env.scale * 0.1;
	else if (keycode == 99)
		all->env.color_offset = all->env.color_offset + 5000;
	else if (keycode == 118)
		all->env.color_offset = all->env.color_offset - 5000;
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

int	handle_mouse(int button, int x, int y, void *param)
{
	t_all	*all;
	double	old_scale;

	all = (t_all *)param;
	old_scale = all->env.scale;
	if (button == 4)
		all->env.scale = all->env.scale * 0.9;
	else if (button == 5)
		all->env.scale = all->env.scale * 1.1;
	all->env.offset_re = all->env.offset_re + (x * (old_scale - all->env.scale))
		/ WIDTH;
	all->env.offset_im = all->env.offset_im + (y * (old_scale - all->env.scale))
		/ HEIGHT;
	render_fractal(all);
	return (0);
}

void	set_env(t_all *all)
{
	all->env.scale = DEFAULT_SCALE;
	all->env.offset_re = DEFAULT_OFFSET_RE;
	all->env.offset_im = DEFAULT_OFFSET_IM;
	all->env.color_offset = DEFAULT_COLOR_OFFSET;
	all->env.mlx = mlx_init();
	all->env.win = mlx_new_window(all->env.mlx, WIDTH, HEIGHT, "fract-ol");
	render_fractal(all);
	mlx_hook(all->env.win, 17, 1L << 17, handle_destroy, NULL);
	mlx_key_hook(all->env.win, handle_key, all);
	mlx_mouse_hook(all->env.win, handle_mouse, all);
	mlx_loop(all->env.mlx);
}

void	render_fractal(t_all *all)
{
	if (all->env.type == MANDELBROT)
		render_mandelbrot(&all->env);
	else if (all->env.type == JULIA)
		render_julia(&all->env, &all->julia);
	else if (all->env.type == BURNING_SHIP)
		render_burning_ship(&all->env);
}

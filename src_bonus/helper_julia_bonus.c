/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_julia.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:02:50 by yutsasak          #+#    #+#             */
/*   Updated: 2025/02/12 17:02:51 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calc_julia(double zx, double zy, t_julia *julia, t_env *env)
{
	int		iter;
	double	tmp;

	iter = 0;
	while ((zx * zx + zy * zy) < 4 && iter < MAX_ITER)
	{
		tmp = zx * zx - zy * zy + julia->c_re;
		zy = 2 * zx * zy + julia->c_im;
		zx = tmp;
		iter++;
	}
	if (iter == MAX_ITER)
		return (0x000000);
	return ((((iter * 0xFFFFFF) / MAX_ITER) + env->color_offset) & 0xFFFFFF);
}

void	render_julia_line(int y, t_env *env, t_julia *julia, t_img *img)
{
	t_point	p;
	int		color;
	double	zx;
	double	zy;

	p.y = y;
	p.x = 0;
	while (p.x < WIDTH)
	{
		zx = p.x * (env->scale / WIDTH) + env->offset_re;
		zy = p.y * (env->scale / HEIGHT) + env->offset_im;
		color = calc_julia(zx, zy, julia, env);
		put_pixel(img, p, color);
		p.x++;
	}
}

void	render_julia_lines(t_env *env, t_julia *julia, t_img *img)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		render_julia_line(y, env, julia, img);
		y++;
	}
}

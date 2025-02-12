/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <sasayu8190@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:02:29 by yutsasak          #+#    #+#             */
/*   Updated: 2025/02/12 17:02:30 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_img *img, t_point p, int color)
{
	int	index;

	index = (p.y * img->size_line) + (p.x * (img->bpp / 8));
	*(int *)(img->data + index) = color;
}

void	render_mandelbrot(t_env *env)
{
	t_img	img;

	img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	img.data = mlx_get_data_addr(img.img, &img.bpp, &img.size_line,
			&img.endian);
	render_mandelbrot_lines(env, &img);
	mlx_put_image_to_window(env->mlx, env->win, img.img, 0, 0);
	mlx_destroy_image(env->mlx, img.img);
}

void	render_julia(t_env *env, t_julia *julia)
{
	t_img	img;

	img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	img.data = mlx_get_data_addr(img.img, &img.bpp, &img.size_line,
			&img.endian);
	render_julia_lines(env, julia, &img);
	mlx_put_image_to_window(env->mlx, env->win, img.img, 0, 0);
	mlx_destroy_image(env->mlx, img.img);
}

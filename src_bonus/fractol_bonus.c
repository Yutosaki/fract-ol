/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:02:29 by yutsasak          #+#    #+#             */
/*   Updated: 2025/02/12 20:08:52 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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
	if (!img.img)
	{
		ft_printf("Error: mlx_new_image failed (mandelbrot)\n");
		exit(1);
	}
	img.data = mlx_get_data_addr(img.img, &img.bpp, &img.size_line,
			&img.endian);
	if (!img.data)
	{
		mlx_destroy_image(env->mlx, img.img);
		ft_printf("Error: mlx_get_data_addr failed (mandelbrot)\n");
		exit(1);
	}
	render_mandelbrot_lines(env, &img);
	mlx_put_image_to_window(env->mlx, env->win, img.img, 0, 0);
	mlx_destroy_image(env->mlx, img.img);
}

void	render_julia(t_env *env, t_julia *julia)
{
	t_img	img;

	img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!img.img)
	{
		ft_printf("Error: mlx_new_image failed (julia)\n");
		exit(1);
	}
	img.data = mlx_get_data_addr(img.img, &img.bpp, &img.size_line,
			&img.endian);
	if (!img.data)
	{
		mlx_destroy_image(env->mlx, img.img);
		ft_printf("Error: mlx_get_data_addr failed (julia)\n");
		exit(1);
	}
	render_julia_lines(env, julia, &img);
	mlx_put_image_to_window(env->mlx, env->win, img.img, 0, 0);
	mlx_destroy_image(env->mlx, img.img);
}

void	render_burning_ship(t_env *env)
{
	t_img	img;

	img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!img.img)
	{
		ft_printf("Error: mlx_new_image failed (burning_ship)\n");
		exit(1);
	}
	img.data = mlx_get_data_addr(img.img, &img.bpp, &img.size_line,
			&img.endian);
	if (!img.data)
	{
		mlx_destroy_image(env->mlx, img.img);
		ft_printf("Error: mlx_get_data_addr failed (burning_ship)\n");
		exit(1);
	}
	render_burning_ship_lines(env, &img);
	mlx_put_image_to_window(env->mlx, env->win, img.img, 0, 0);
	mlx_destroy_image(env->mlx, img.img);
}

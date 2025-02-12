/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:02:55 by yutsasak          #+#    #+#             */
/*   Updated: 2025/02/12 20:09:10 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	print_usage(char *prog)
{
	ft_printf("Usage: %s [mandelbrot | julia <julia_c_re> <julia_c_im> |"
		" burning_ship]\n", prog);
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static double	process_fraction(const char *str, int *i)
{
	double	f;
	double	d;

	f = 0.0;
	d = 10.0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		f = f + (str[*i] - '0') / d;
		d = d * 10.0;
		(*i) = (*i) + 1;
	}
	return (f);
}

double	ft_atof(const char *str)
{
	double	res;
	double	sign;
	int		i;
	double	f;

	res = 0.0;
	sign = 1.0;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1.0;
		i = i + 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10.0 + (str[i] - '0');
		i = i + 1;
	}
	if (str[i] == '.')
	{
		i = i + 1;
		f = process_fraction(str, &i);
		res = res + f;
	}
	return (res * sign);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc < 2 || argc > 4)
		print_usage(argv[0]);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		all.env.type = MANDELBROT;
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		all.env.type = JULIA;
		if (argc == 4)
		{
			all.julia.c_re = ft_atof(argv[2]);
			all.julia.c_im = ft_atof(argv[3]);
		}
		else
		{
			all.julia.c_re = -0.7;
			all.julia.c_im = 0.27015;
		}
	}
	else if (ft_strcmp(argv[1], "burning_ship") == 0)
		all.env.type = BURNING_SHIP;
	else
		print_usage(argv[0]);
	set_env(&all);
}

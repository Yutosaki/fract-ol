/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:02:55 by yutsasak          #+#    #+#             */
/*   Updated: 2025/02/12 22:43:35 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		f = process_fraction(str, &i);
		res = res + f;
	}
	return (res * sign);
}

void	print_usage(const char *prog)
{
	ft_printf("Usage: %s [mandelbrot | julia <julia_c_re> <julia_c_im>] |"
				" [burning_ship]\n",
				prog);
	exit(1);
}

void	error_and_usage(const char *msg, const char *prog)
{
	ft_printf("Error: %s\n", msg);
	print_usage(prog);
}

int	main(int argc, char **argv)
{
	t_all	all;

	parse_arguments(argc, argv, &all);
	set_env(&all);
	return (0);
}

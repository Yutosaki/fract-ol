/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:15:17 by yutsasak          #+#    #+#             */
/*   Updated: 2025/02/12 22:43:41 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	validate_number(const char *s, const char *err_msg, const char *prog)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i] || !ft_isdigit(s[i]))
		error_and_usage(err_msg, prog);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] == '.')
	{
		i++;
		if (!s[i] || !ft_isdigit(s[i]))
			error_and_usage(err_msg, prog);
		while (s[i] && ft_isdigit(s[i]))
			i++;
	}
	if (s[i] != '\0')
		error_and_usage(err_msg, prog);
}

void	parse_arguments(int argc, char **argv, t_all *all)
{
	if (argc < 2 || argc > 4)
		print_usage(argv[0]);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		parse_mandelbrot_args(argc, argv, all);
	else if (ft_strcmp(argv[1], "julia") == 0)
		parse_julia_args(argc, argv, all);
	else if (ft_strcmp(argv[1], "burning_ship") == 0)
		parse_burning_ship_args(argc, argv, all);
	else
		error_and_usage("unknown fractal name", argv[0]);
}

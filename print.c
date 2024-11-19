/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:47:07 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/15 10:47:07 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(const char c, int *counter)
{
	*counter += write(1, &c, 1);
}

void	ft_putstr(const char *str, int *counter)
{
	if (!str)
	{
		ft_putstr("(null)", counter);
		return ;
	}
	while (*str)
		ft_putchar(*str++, counter);
}

void	print_u(unsigned int n, int *counter)
{
	if (n > 9)
		print_u(n / 10, counter);
	ft_putchar(n % 10 + '0', counter);
}

void	print_d(int n, int *counter)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putstr("-2147483648", counter);
			return ;
		}
		ft_putchar('-', counter);
		return (print_d(-n, counter));
	}
	if (n > 9)
	{
		print_d(n / 10, counter);
		ft_putchar(n % 10 + '0', counter);
		return ;
	}
	else
		ft_putchar(n + '0', counter);
	return ;
}

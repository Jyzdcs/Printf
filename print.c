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

#include "printf.h"

void	ft_putchar(const char c)
{
	write(1, &c, 1);
}

int	ft_putstr(const char *str)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		ft_putchar(*str++);
		counter++;
	}
	return (counter);
}

int	print_u(unsigned int n)
{	
	int	counter;

	counter = 0;
	while (n)
	{
		ft_putchar(n % 10 + '0');
		n /= 10;
		counter++;
	}
	return (counter);
}

int	print_d(int n, int fd, int counter)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putstr("-2147483648");
			return (11);
		}
		ft_putchar('-');
		return (print_d(-n, fd, counter + 1));
	}
	if (n > 9)
	{
		counter = print_d(n / 10, fd, counter + 1);
		ft_putchar(n % 10 + '0');
		return (counter);
	}
	else
		ft_putchar(n + '0');
	return (1);
}

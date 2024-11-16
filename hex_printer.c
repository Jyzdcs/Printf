/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:49:54 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/15 10:49:54 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_base(int nb, int maj)
{
	const char	*base_1 = "0123456789abcdef";
	const char	*base_2 = "0123456789ABCDEF";

	if (maj)
		write(1, &base_2[nb], 1);
	else
		write(1, &base_1[nb], 1);
	return (1);
}

int	ft_print_0x(void)
{
	write(1, "0x", 2);
	return (2);
}

int	ft_putnbr_base(unsigned long nbr, int r, int maj)
{
	int	counter;

	counter = 1;
	if (r == 1)
		counter += ft_print_0x();
	if (nbr >= 16)
	{
		counter += ft_putnbr_base(nbr / 16, 0, maj);
		ft_putnbr_base(nbr % 16, 0, maj);
	}
	else
		ft_putchar_base(nbr, maj);
	return (counter);
}

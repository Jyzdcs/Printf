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

void	ft_putchar_base(int nb, int maj, int *counter)
{
	const char	*base_1 = "0123456789abcdef";
	const char	*base_2 = "0123456789ABCDEF";

	if (maj)
		*counter += write(1, &base_2[nb], 1);
	else
		*counter += write(1, &base_1[nb], 1);
}

void	ft_print_0x(int *counter)
{
	*counter += write(1, "0x", 2);
}

void	ft_putnbr_base(unsigned long nbr, int r, int maj, int *counter)
{
	if (nbr == 0 && r)
	{
		ft_putstr("(nil)", counter);
		return ;
	}
	if (r == 1)
		ft_print_0x(counter);
	if (nbr > 15)
	{
		ft_putnbr_base(nbr / 16, 0, maj, counter);
		ft_putchar_base(nbr % 16, maj, counter);
		return ;
	}
	ft_putchar_base(nbr % 16, maj, counter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:25:54 by bnafiai           #+#    #+#             */
/*   Updated: 2024/11/22 15:25:55 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr_d(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putchar('-');
		count += ft_putchar('2');
		count += ft_putnbr_d(147483648);
	}
	else if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
		count += ft_putnbr_d(n);
	}
	else if (n >= 10)
	{
		count += ft_putnbr_d(n / 10);
		count += ft_putnbr_d(n % 10);
	}
	else
		count += ft_putchar(n + '0');
	return (count);
}

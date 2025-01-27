/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:55:18 by bnafiai           #+#    #+#             */
/*   Updated: 2025/01/14 17:34:36 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(char spe, va_list lst)
{
	int	i;

	i = 0;
	if (spe == 'c')
		i += ft_printf_char(va_arg(lst, int));
	else if (spe == 's')
		i += ft_printf_string(va_arg(lst, char *));
	else if (spe == 'd' || spe == 'i')
		i += ft_putnbr_d(va_arg(lst, int));
	else if (spe == '%')
		i += write(1, "%", 1);
	else
		i += write(1, &spe, 1);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	lst;
	int		count;

	va_start(lst, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += print_format(*(++format), lst);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(lst);
	return (count);
}

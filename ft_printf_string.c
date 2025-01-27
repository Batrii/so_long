/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:25:40 by bnafiai           #+#    #+#             */
/*   Updated: 2025/01/12 14:55:58 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_string(char *s)
{
	int	i;
	int	count;

	count = 0;
	if (!s)
		return (count + write(1, "(null)", 6));
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
		count++;
	}
	return (count);
}

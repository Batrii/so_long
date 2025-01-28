/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:38:28 by bnafiai           #+#    #+#             */
/*   Updated: 2025/01/28 14:00:14 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ext(char *str, char *ber)
{
	int	i;
	int	len_str;
	int	len_ber;

	len_str = my_strlen2(str);
	len_ber = my_strlen2(ber);
	if (len_str < len_ber + 1 || str[len_str - len_ber - 1] == '/')
		return (0);
	i = 0;
	while (ber[i] && str[len_str - len_ber + i] == ber[i])
		i++;
	if (ber[i] == '\0')
		return (1);
	return (0);
}

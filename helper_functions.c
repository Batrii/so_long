/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:30:39 by bnafiai           #+#    #+#             */
/*   Updated: 2025/01/19 16:08:03 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	*my_strchr2(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)(str + i));
	}
	return (NULL);
}

size_t	my_strlen2(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	rep_fun(t_data *game, void *i, int x, int y)
{
	return (mlx_put_image_to_window(game->mlx, game->win, i, x, y));
}

char	*my_strdup3(char *str)
{
	char	*dup;
	int		i;
	size_t	len;

	len = my_strlen2(str) + 1;
	dup = malloc(sizeof(char) * len);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
